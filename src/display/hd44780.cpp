/* 
    Title --- display/hd44780.cpp

    Copyright (C) 2013 Giacomo Trudu - wicker25[at]gmail[dot]com

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

namespace rpihw { // Begin main namespace

namespace display { // Begin displays namespace

hd44780::hd44780( uint8_t rs, uint8_t e,
				  uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7 )

	: m_mode( new iface::output( { rs, e } ) )
	, m_data( new iface::output( { d4, d5, d6, d7 } ) ) {

}

hd44780::hd44780( uint8_t rs, uint8_t e,
				  uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
				  uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7 )

	: m_mode( new iface::output( { rs, e } ) )
	, m_data( new iface::output( { d0, d1, d2, d3, d4, d5, d6, d7 } ) ) {

}

hd44780::~hd44780() {

	// Destroy the interfaces
	delete m_mode;
	delete m_data;
}

void
hd44780::init( uint8_t cols, uint8_t rows, bool font ) {

	// Store the size of the display
	m_width		= cols;
	m_height	= math::min< uint8_t >( rows, 4 );

	// Create a new character buffer
	m_buffer.assign( m_width * m_height, ' ' );

	// Store the font size
	m_font_height = font ? 10 : 8;

	// Set the address locations
	// see: http://web.alfredstate.edu/weimandn/lcd/lcd_addressing/lcd_addressing_index.html
	m_lines[0] = 0x00;
	m_lines[1] = 0x40;

	if ( m_height == 4 && m_width == 16 ) {

		m_lines[2] = 0x10;
		m_lines[3] = 0x50;

	} else {

		m_lines[2] = 0x14;
		m_lines[3] = 0x54;
	}


	// Wait 20ms for LCD to power up
	time::msleep( 20 );

	// Initialize the display
	uint8_t flags = FUNC | FUNC_DL;

	// If required, enable the 4-bit mode
	if ( m_data->size() == 4 ) {

		flags >>= 4;

		sendData( flags, 5000 );
		sendData( flags, 200 );
		sendData( flags, 200 );

		flags = FUNC;
		sendData( flags >> 4, 5000 );

	} else {

		sendData( flags, 5000 );
		sendData( flags, 200 );
		sendData( flags, 200 );
	}

	// Apply settings
	if ( m_height > 1 )			flags |= FUNC_N;
	if ( m_font_height == 10 )	flags |= FUNC_F; 

	cmd( flags );
	cmd( POWER | POWER_D );
	cmd( ENTRY | ENTRY_ID );
	cmd( CLEAR );

	// Set the initial cursor position
	move( 0, 0 );
}

void
hd44780::strobe() {

	// Toggle the enable pin
	m_mode->write( 1, 1 );
	time::usleep( 50 );
	m_mode->write( 1, 0 );
}

void
hd44780::sendData( uint8_t data, size_t delay ) {

	// Send the nibble to the display
	m_data->write( data );

	// Toggle the enable pin
	strobe();

	// Wait some time
	time::usleep( delay );
}

void
hd44780::sendSerial( uint8_t data, size_t delay ) {

	// If the display uses 4-bit mode send the high nibble
	if ( m_data->size() == 4 )
		sendData( data >> 4, delay );

	// Send rest of data to the display
	sendData( data, delay );
}

void
hd44780::home() {

	// Home the cursor
	cmd( HOME );

	// Reset the cursor position
	m_pos_x = m_pos_y = 0;
}

void
hd44780::move( uint8_t x, uint8_t y ) {

	// Check if position exists
	if ( x >= m_width || y >= m_height )
		throw exception( utils::format( "(Fatal) `hd44780::move`: the position (%u,%u) does not exists\n", x, y ) );

	// Update the cursor position
	m_pos_x = x;
	m_pos_y = y;

	// Set the position of the cursor on the display
	cmd( DDRAM | ( m_lines[y] + x ) );
}

void
hd44780::putChar( uint8_t c ) {

	// Set RS value to high
	m_mode->write( 0, 1 );

	// Send the character to the display
	sendSerial( c, 200 );

	// Copy the character into the buffer
	m_buffer[ m_pos_x + m_pos_y * m_width ] = c;

	// Increment the x-position of the cursor 
	++m_pos_x;
}

void
hd44780::newLine() {

	// If there are still lines available move the cursor to the next line 
	if ( m_pos_y < m_height - 1 ) move( 0, m_pos_y + 1 );

	// Else move the cursor to the first column and scroll up the contents
	else if ( m_autoscroll & VSCROLL ) {

		move( 0, m_pos_y );
		scrollUp( false );

	// Else clear the display
	} else clear();
}

void
hd44780::write( uint8_t c ) {

	// Parse the character
	switch ( c ) {

		// Carriage-return character
		case '\r': { move( 0, m_pos_y ); break; }

		// New-line character
		case '\n': { newLine(); break; }

		// Normal character
		default: {

			// Check if there are no places available in the line
			if ( m_pos_x == m_width ) {

				// Make room for the new character
				if ( m_autoscroll & HSCROLL )
					scrollLeft();

				else if ( m_autoscroll & HSCROLL_LINE )
					scrollLeftLine( m_pos_y );

				else newLine();
			}

			// Put the character on the display
			putChar( c );

			// Wait some time (corresponding to the typing delay)
			if ( m_typing_delay && !std::isspace( c ) )
				time::msleep( m_typing_delay );

			break;
		}
	}
}

void
hd44780::write( const std::string &text ) {

	// Write the string on the display
	for ( auto &c : text ) {

		// Put the character on the display
		write( (uint8_t) c );
	}
}

void
hd44780::scrollLeft( bool cursor ) {

	// Hardware: cmd( SHIFT | SHIFT_SC );

	// Store the cursor position
	uint8_t x = m_pos_x - (uint8_t) cursor,
			y = m_pos_y;

	// Iterators
	uint8_t i, j;

	// Move left the contents
	for ( j = 0; j < m_height; ++j ) {

		move( 0, j );

		for ( i = 0; i < m_width - 1; ++i )
			putChar( getChar( i + 1, j ) );
	}

	// Clear the last column
	for ( i = m_width - 1, j = 0; j < m_height; ++j ) {

		move( i, j ); putChar( ' ' );
	}

	// Restore the cursor position
	move( x, y );
}

void
hd44780::scrollRight( bool cursor ) {

	// Hardware: cmd( SHIFT | SHIFT_SC | SHIFT_R );

	// Store the cursor position
	uint8_t x = m_pos_x + (uint8_t) cursor,
			y = m_pos_y;

	// Iterators
	uint8_t i, j;

	// Move right the contents
	for ( j = 0; j < m_height; ++j ) {

		for ( i = m_width - 1; i >= 1; --i )
			m_buffer[ i + j * m_width ] = getChar( i - 1, j );

		move( 1, j );

		for ( i = 1; i < m_width; ++i )
			putChar( getChar( i, j ) );
	}

	// Clear the first column
	for ( i = 0, j = 0; j < m_height; ++j ){

		move( i, j ); putChar( ' ' );
	}

	// Restore the cursor position
	move( x, y );
}

void
hd44780::scrollUp( bool cursor ) {

	// Store the cursor position
	uint8_t x = m_pos_x,
			y = m_pos_y - (uint8_t) cursor;

	// Iterators
	uint8_t i, j;

	// Move up the contents
	for ( j = 0; j < m_height - 1; ++j ) {

		move( 0, j );

		for ( i = 0; i < m_width; ++i )
			putChar( getChar( i, j + 1 ) );
	}

	// Clear the last row
	move( 0, m_height - 1 );

	for ( i = 0; i < m_width; ++i )
		putChar( ' ' );

	// Restore the cursor position
	move( x, y );
}

void
hd44780::scrollDown( bool cursor ) {

	// Store the cursor position
	uint8_t x = m_pos_x,
			y = m_pos_y + (uint8_t) cursor;

	// Iterators
	uint8_t i, j;

	// Move down the contents
	for ( j = m_height - 1; j >= 1; --j ) {

		move( 0, j );

		for ( i = 0; i < m_width; ++i )
			putChar( getChar( i, j - 1 ) );
	}

	// Clear the first row
	move( 0, 0 );

	for ( i = 0; i < m_width; ++i )
		putChar( ' ' );

	// Restore the cursor position
	move( x, y );
}

void
hd44780::scrollLeftLine( uint8_t line, bool cursor ) {

	// Store the cursor position
	uint8_t x = m_pos_x - (uint8_t) cursor,
			y = m_pos_y;

	// Iterator
	uint8_t i;

	// Scroll the line to the left
	move( 0, line );

	for ( i = 0; i < m_width - 1; ++i )
		putChar( getChar( i + 1, line ) );

	putChar( ' ' );

	// Restore the cursor position
	move( x, y );
}

void
hd44780::scrollRightLine( uint8_t line, bool cursor ) {

	// Store the cursor position
	uint8_t x = m_pos_x + (uint8_t) cursor,
			y = m_pos_y;

	// Iterator
	uint8_t i;

	// Scroll the line to the right
	for ( i = m_width - 1; i >= 1; --i )
		m_buffer[ i + line * m_width ] = getChar( i - 1, line );

	move( 0, line ); putChar( ' ' );

	for ( i = 1; i < m_width; ++i )
		putChar( getChar( i, line ) );

	// Restore the cursor position
	move( x, y );
}

void
hd44780::defChar( uint8_t index, const uint8_t *data ) {

	// Check if custom character is valid
	if ( index > 7 )
		throw exception( "(Fatal) `hd44780::defChar`: could not define new custom character, index out of range\n" );

	// Start definition of the custom character
	cmd( CGRAM | ( index * 8 ) );

	// Set RS value to high
	m_mode->write( 0, 1 );

	// Iterator
	uint8_t i = 0;

	// Define the custom character
	for ( ; i < m_font_height; ++i )
		sendSerial( data[i], 5000 );

	// Restore the cursor position
	move( m_pos_x, m_pos_y );
}

void
hd44780::setCursor( uint8_t mode ) {

	// Set the cursor mode
	uint8_t flags = POWER | POWER_D;

	if ( mode & CURSOR_SOLID )		flags |= POWER_C; 
	if ( mode & CURSOR_BLINKING )	flags |= POWER_B; 

	cmd( flags );
}

void
hd44780::clear() {

	// Clear the display
	cmd( CLEAR );

	// Reset the cursor position
	m_pos_x = m_pos_y = 0;

	// Clear the character buffer
	m_buffer.assign( m_buffer.size(), ' ' );
}

} // End of displays namespace

} // End of main namespace

#endif /* _RPI_HW_DISPLAY_HD44780_CPP_ */
