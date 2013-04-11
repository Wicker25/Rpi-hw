/* 
	Title --- display/pcd8544.cpp

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


#ifndef _RPI_HW_DISPLAY_PCD8544_CPP_
#define _RPI_HW_DISPLAY_PCD8544_CPP_

#include <rpi-hw/display/pcd8544.hpp>

#include <rpi-hw/utils.hpp>
#include <rpi-hw/utils-inl.hpp>

#include <rpi-hw/time.hpp>
#include <rpi-hw/time-inl.hpp>

#include <rpi-hw/bitset.hpp>
#include <rpi-hw/bitset-inl.hpp>

#include <rpi-hw/font/base.hpp>
#include <rpi-hw/font/base-inl.hpp>

#include <rpi-hw/font/freetype.hpp>
#include <rpi-hw/font/freetype-inl.hpp>

#include <rpi-hw/designer.hpp>
#include <rpi-hw/designer-inl.hpp>

#include <rpi-hw/gpio.hpp>
#include <rpi-hw/gpio-inl.hpp>

#include <rpi-hw/iface/base.hpp>
#include <rpi-hw/iface/base-inl.hpp>

#include <rpi-hw/iface/output.hpp>
#include <rpi-hw/iface/output-inl.hpp>

#include <rpi-hw/iface/input.hpp>
#include <rpi-hw/iface/input-inl.hpp>

#include <rpi-hw/iface/shiftout.hpp>
#include <rpi-hw/iface/shiftout-inl.hpp>

#include <rpi-hw/display/pcd8544-inl.hpp>

namespace rpihw { // Begin main namespace

namespace display { // Begin displays namespace

pcd8544::pcd8544( uint8_t sclk, uint8_t sdin, uint8_t dc, uint8_t sce, uint8_t rst ) : designer< int8_t, bool >( LCD_WIDTH, LCD_HEIGHT ) {

	// Create the interfaces to the display
	m_control	= new iface::output( 3, dc, sce, rst );
	m_data		= new iface::shiftOut( sdin, sclk, iface::shiftOut::MSBFIRST, 10000 );

	// Calculate the size of the data buffer
	size_t buffer_size = LCD_WIDTH * LCD_HEIGHT / 8;

	// Create the data buffer
	m_buffer = utils::malloc< uint8_t >( buffer_size, 0x00 );

	// Create the update buffer
	m_updates = new bitset( buffer_size, true );

	// Set the foreground color
	setColor( COLOR_BLACK );
}

pcd8544::~pcd8544() {

	// Destroy the interfaces
	delete m_control;
	delete m_data;

	// Destroy the data buffer
	delete[] m_buffer;

	// Destroy the update buffer
	delete m_updates;
}

void
pcd8544::init( uint8_t contrast, bool inverse ) {

	// Enalbe the display chip
	m_control->write( SCE, 0 );

	// Reset the display
	m_control->write( RST, 0 );
	time::usleep( 10 );
	m_control->write( RST, 1 );

	// Initialize the display
	cmd( FUNC | FUNC_H );
	cmd( BIAS | 0x04 );
	cmd( VOP | ( contrast & 0x7f ) );
	cmd( FUNC );
	cmd( DISPLAY | DISPLAY_D | ( DISPLAY_E * (uint8_t) inverse ) );

	// Update the display
	redraw();
}

void
pcd8544::cmd( uint8_t data ) {

	// Set DC value to low
	m_control->write( DC, 0 );

	// Send the command to the display
	m_control->write( SCE, 0 );
	m_data->write( data );
	m_control->write( SCE, 1 );
}

void
pcd8544::sendData( uint8_t data ) {

	// Set DC value to high
	m_control->write( DC, 1 );

	// Send the data to the display
	m_control->write( SCE, 0 );
	m_data->write( data );
	m_control->write( SCE, 1 );
}

void
pcd8544::setContrast( uint8_t value ) {

	// Set the contrast of the display
	cmd( FUNC | FUNC_H );
	cmd( VOP | ( value & 0x7f ) );
	cmd( FUNC );
}

void
pcd8544::setPixel( int8_t x, int8_t y, bool color ) {

	// Check if positions exist
	if ( x < 0 || y < 0 || x >= LCD_WIDTH || y >= LCD_HEIGHT )
		return;

	// Calculate the bit position
	uint8_t shift = (uint8_t) ( y % 8 );

	// Set the color of the pixel
	size_t index = (size_t) x + ( (size_t) y / 8 ) * LCD_WIDTH;

	if ( color )
		m_buffer[ index ] |= ( 1 << shift );
	else
		m_buffer[ index ] &= ~( 1 << shift );

	// Add the update to the buffer
	m_updates->set( index, true );
}

bool
pcd8544::getPixel( int8_t x, int8_t y ) const {

	// Check if position exists 
	if ( x < 0 || y < 0 || x >= LCD_WIDTH || y >= LCD_HEIGHT )
		return 0;

	// Set the color of the pixel
	return (bool) ( m_buffer[ (size_t) x + ( (size_t) y / 8 ) * LCD_WIDTH ] >> ( 7 - ( y % 8 ) ) & 0x01 );
}

uint16_t
pcd8544::redraw() {

	// Update the pixels in the bounding box
	uint16_t total = 0, j = 0, i = 0;

	bool jump = true;

	for ( ; i < m_updates->size(); i++, j = i % LCD_WIDTH ) {

		if ( j == 0 )
			cmd( YADDR | i / LCD_WIDTH );

		if ( m_updates->get( i ) ) {

			if ( jump ) {

				cmd( XADDR | j );
				jump = false;
			}

			sendData( m_buffer[ i ] );
			total++;

		} else jump = true;
	}

	// Remove all updates from the buffer
	m_updates->set( false );

	// Return the number of updated blocks
	return total;
}

void
pcd8544::clear() {

	// Clear the data buffer
	utils::memset< uint8_t >( m_buffer, LCD_WIDTH * LCD_HEIGHT / 8, 0x00 );

	// Add the update to the buffer
	m_updates->set( true );

	// Restore the cursor position
	move( 0, 0 );
}

} // End of displays namespace

} // End of main namespace

#endif
