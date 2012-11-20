/* 
    Title --- display/hd44780.cpp

    Copyright (C) 2012 Giacomo Trudu - wicker25[at]gmail[dot]com

    This file is part of Rpi-hw.

    Rpi-hw is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation version 3 of the License.

    Rpi-hw is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Rpi-hw. If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef _RPI_HW_DISPLAY_HD44780_CPP_
#define _RPI_HW_DISPLAY_HD44780_CPP_

#include <rpi-hw/display/hd44780.hpp>

#include <rpi-hw/utils.hpp>
#include <rpi-hw/utils-inl.hpp>

#include <rpi-hw/mutex.hpp>
#include <rpi-hw/mutex-inl.hpp>

#include <rpi-hw/thread.hpp>
#include <rpi-hw/thread-inl.hpp>

#include <rpi-hw/gpio.hpp>
#include <rpi-hw/gpio-inl.hpp>

#include <rpi-hw/iface/base.hpp>
#include <rpi-hw/iface/base-inl.hpp>

#include <rpi-hw/iface/output.hpp>
#include <rpi-hw/iface/output-inl.hpp>

#include <rpi-hw/iface/input.hpp>
#include <rpi-hw/iface/input-inl.hpp>

#include <rpi-hw/display/hd44780-inl.hpp>

namespace rpihw { // Begin main namespace

namespace display { // Begin displays namespace

// Address locations
const uint8_t hd44780::lines[4] = { 0x00, 0x40, 0x14, 0x54 };

hd44780::hd44780( uint8_t rs, uint8_t e,
				  uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3 ) : m_cols(0), m_rows(0), m_size(0) {

	// Create the output interfaces to the display
	m_mode = new iface::output( 2, rs, e );
	m_data = new iface::output( 4, d0, d1, d2, d3 );
}

hd44780::hd44780( uint8_t rs, uint8_t e,
				  uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
				  uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7 ) : m_cols(0), m_rows(0), m_size(0) {

	// Create the output interfaces to the display
	m_mode = new iface::output( 2, rs, e );
	m_data = new iface::output( 8, d0, d1, d2, d3, d4, d5, d6, d7 );
}

hd44780::~hd44780() {

	// Destroy the output interfaces
	delete m_mode;
	delete m_data;

	// Delete the character buffer
	if ( m_size ) delete m_buffer;
}

void
hd44780::init( uint8_t cols, uint8_t rows, bool font ) {

	// Store the size of the display
	m_cols = cols;
	m_rows = rows;

	// Store the font size
	m_font_height = ( font ? 10 : 8 );

	// Delete the old character buffer
	if ( m_size ) delete m_buffer;

	// Create a new character buffer
	m_size = m_cols * m_rows;
	m_buffer = utils::malloc< uint8_t >( m_size, ' ' );

	// Set the initial cursor position
	move( 0, 0 );

	// Wait 20ms for LCD to power up
	utils::msleep( 20 );

	// Initialize the display
	uint8_t flags = FUNC | FUNC_DL;

	// If required, enable the 4-bit mode
	if ( m_data->numOfPins() == 4 ) {

		flags >>= 4;

		send( flags, 5000 );
		send( flags, 200 );
		send( flags, 200 );

		flags = FUNC;
		send( flags >> 4, 5000 );

	} else {

		send( flags, 5000 );
		send( flags, 200 );
		send( flags, 200 );
	}

	// Apply settings
	if ( m_rows > 1 ) flags |= FUNC_N;
	if ( m_font_height == 10 ) flags |= FUNC_F; 

	cmd( flags );
	cmd( POWER | POWER_D );
	cmd( ENTRY | ENTRY_ID );
	cmd( CLEAR );

	setAutoscroll( VSCROLL );
}

void
hd44780::strobe() {

	// Toggle the enable pin
	m_mode->write( 1, 1 );
	utils::usleep( 50 );
	m_mode->write( 1, 0 );
}

void
hd44780::send( uint8_t data, size_t wait ) {

	// Send nibble to the display
	m_data->write( data );

	// Toggle the enable pin
	strobe();

	// Wait some time
	utils::usleep( (useconds_t) wait );
}

void
hd44780::sendSerial( uint8_t data, size_t wait ) {

	// If 4-bit mode is used, send high nibble to the display
	if ( m_data->numOfPins() == 4 )
		send( data >> 4, wait );

	// Send rest of data to the display
	send( data, wait );
}

void
hd44780::putchar( uint8_t chr ) {

	// Set RS value to high
	m_mode->write( 0, 1 );

	// Send the character to the display
	sendSerial( chr, 200 );

	// Store the character into the buffer
	m_buffer[ m_pos[0] + m_pos[1] * m_cols ] = chr;

	// Update the cursor position
	m_pos[0]++;
}

void
hd44780::home() {

	// Home the cursor
	cmd( HOME );

	// Update the cursor position
	m_pos[0] = m_pos[1] = 0;;
}

void
hd44780::clear() {

	// Clear the screen
	cmd( CLEAR );

	// Update the cursor position
	m_pos[0] = m_pos[1] = 0;

	// Clear the character buffer
	utils::memset< uint8_t >( m_buffer, m_size, ' ' );
}

void
hd44780::move( uint8_t x, uint8_t y ) {

	// Check if position exists
	if ( x >= m_cols || y >= m_rows )
		throw exception( utils::format( "(Error) `hd44780::move`: the position (%u,%u) does not exists\n", x, y ) );

	// Update the cursor position
	m_pos[0] = x;
	m_pos[1] = y;

	// Set the position of the cursor on the display
	cmd( DGRAM | ( hd44780::lines[y] + x ) );
}

void
hd44780::newLine() {

	// Check if there are still lines available
	if ( m_pos[1] < m_rows - 1 ) move( 0, m_pos[1] + 1 );

	// Scroll up the contents and move the cursor to the new line
	else if ( m_autoscroll & VSCROLL ) {

		move( 0, m_pos[1] );
		scrollUp( false );

	// Clear the display
	} else clear();
}

void
hd44780::write( uint8_t chr ) {

	// Check if there are no still spaces available in the row
	if ( isLineFull() ) {

		// Make new space for the character
		if ( m_autoscroll & HSCROLL )
			scrollLeft();

		else if ( m_autoscroll & HSCROLL_LINE )
			scrollLeftLine( m_pos[1] );

		else newLine();

		// Write the character on the display, but ignore other new line character
		if ( chr != '\n' ) putchar( chr );

	} else {

		// Write the character on the display
		putchar( chr );
	}
}

void
hd44780::write( const std::string &text, size_t delay ) {

	// Iterator
	size_t i = 0;

	// Send the string to the display, parsing new lines
	for ( ; i < text.size(); i++ ) {

		// Parse newline characters
		if ( text[i] == '\n' ) {

			// Move the cursor to the new line
			newLine();

		} else {

			// Write the character on the display and wait some time
			write( text[i] );

			if ( text[i] != ' ' ) utils::msleep( delay );
		}
	}
}

void
hd44780::scrollLeft( bool cursor ) {

	// Hardware: cmd( SHIFT | SHIFT_SC );

	// Store the cursor position
	uint8_t x = m_pos[0] - 1, y = m_pos[1];

	// Iterator
	uint8_t i = 0;

	// Move left the contents and delete the first column
	for ( ; i < m_size; i++ ) {

		if ( i % m_cols == 0 ) move( 0, i / m_cols );
		putchar( ( i + 1 ) % m_cols != 0 ? m_buffer[ i + 1 ] : ' ' );
	}

	// Restore the cursor position
	move( x, y );
}

void
hd44780::scrollRight( bool cursor ) {

	// Hardware: cmd( SHIFT | SHIFT_SC | SHIFT_RL );

	// Store the cursor position
	uint8_t x = m_pos[0] + (uint8_t) cursor,
			y = m_pos[1];

	// Copy the current character buffer
	uint8_t *tmp = utils::malloc< uint8_t >( m_size, m_buffer );

	// Iterator
	uint8_t i = 0;

	// Move right the contents and delete the first column
	for ( ; i < m_size; i++ ) {

		if ( i % m_cols == 0 ) move( 0, i / m_cols );
		putchar( i % m_cols != 0 ? tmp[ i - 1 ] : ' ' );
	}

	// Free the memory
	delete[] tmp;

	// Restore the cursor position
	move( x, y );
}

void
hd44780::scrollUp( bool cursor ) {

	// Store the cursor position
	uint8_t x = m_pos[0],
			y = m_pos[1] - (uint8_t) cursor;

	// Iterator
	uint8_t i = 0;

	// Move up the contents and delete the last row
	for ( ; i < m_size - m_cols; i++ ) {

		if ( i % m_cols == 0 ) move( 0, i / m_cols );
		putchar( m_buffer[ i + m_cols ] );
	}

	move( 0, m_pos[1] + 1 );

	for ( ; i < m_size; i++ ) putchar( ' ' );

	// Restore the cursor position
	move( x, y );
}

void
hd44780::scrollDown( bool cursor ) {

	// Store the cursor position
	uint8_t x = m_pos[0],
			y = m_pos[1] + (uint8_t) cursor;

	// Copy the current character buffer
	uint8_t *tmp = utils::malloc< uint8_t >( m_size, m_buffer );

	// Move the cursor to the first position
	move( 0, 0 );

	// Iterator
	uint8_t i = 0;

	// Move down the contents and delete the first row
	for ( ; i < m_cols; i++ ) putchar( ' ' );

	for ( ; i < m_size; i++ ) {

		if ( i % m_cols == 0 ) move( 0, i / m_cols );
		putchar( tmp[ i - m_cols ] );
	}

	// Free the memory
	delete[] tmp;

	// Restore the cursor position
	move( x, y );
}

void
hd44780::scrollLeftLine( uint8_t line, bool cursor ) {

	// Store the cursor position
	uint8_t x = m_pos[0] - (uint8_t) cursor,
			y = m_pos[1];

	// Iterator
	uint8_t i;

	// Scroll the line to the left
	move( 0, line );

	for ( i = 0; i < m_cols - 1; i++ )
		putchar( m_buffer[ line * m_cols + i + 1 ] );

	putchar( ' ' );

	// Restore the cursor position
	move( x, y );
}

void
hd44780::scrollRightLine( uint8_t line, bool cursor ) {

	// Store the cursor position
	uint8_t x = m_pos[0] + (uint8_t) cursor,
			y = m_pos[1];

	// Copy the current character buffer
	uint8_t *tmp = utils::malloc< uint8_t >( m_size, m_buffer );

	// Iterator
	uint8_t i;

	// Scroll the line to the right
	move( 0, line );

	putchar( ' ' );

	for ( i = 1; i < m_cols; i++ )
		putchar( tmp[ line * m_cols + i - 1 ] );

	// Restore the cursor position
	move( x, y );

	// Free the memory
	delete[] tmp;
}

void
hd44780::defChar( uint8_t index, const uint8_t *data ) {

	// Check if custom character
	if ( index > 7 )
		throw exception( "(Error) `hd44780::defChar`: could not define new custom character, index out of range\n" );

	// Start definition of the custom character
	cmd( CGRAM | ( index * 8 ) );

	// Set RS value to high
	m_mode->write( 0, 1 );

	// Iterator
	uint8_t i = 0;

	// Define the custom character
	for ( ; i < m_font_height; i++ ) sendSerial( data[i], 5000 );

	// Restore the cursor position
	move( m_pos[0], m_pos[1] );
}

void
hd44780::setCursor( uint8_t mode ) {

	// Set the cursor mode
	uint8_t flags = POWER | POWER_D;

	if ( mode & CURSOR_SOLID ) flags |= POWER_C; 
	if ( mode & CURSOR_BLINKING ) flags |= POWER_B; 

	cmd( flags );
}

} // End of displays namespace

} // End of main namespace

#endif
