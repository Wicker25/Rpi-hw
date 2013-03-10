/* 
    Title --- display/pcd8544.cpp

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


#ifndef _RPI_HW_DISPLAY_PCD8544_CPP_
#define _RPI_HW_DISPLAY_PCD8544_CPP_

#include <rpi-hw/display/pcd8544.hpp>

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

#include <rpi-hw/display/pcd8544-inl.hpp>

namespace rpihw { // Begin main namespace

namespace display { // Begin displays namespace

pcd8544::pcd8544( uint8_t sclk, uint8_t sdin, uint8_t dc, uint8_t sce, uint8_t reset ) {

	// Create the output interfaces to the display
	m_data = new iface::output( 5, sclk, sdin, dc, sce, reset );
}

pcd8544::~pcd8544() {

	// Destroy the output interfaces
	delete m_data;
}

void
pcd8544::init() {

	m_data->write( SCLK, 1 );
	m_data->write( SCLK, 0 );

	send( 0x21 );
	send( 0xB1 );
	send( 0x04 );
	send( 0x14 );
	send( 0x0C );
	send( 0x20 );
	send( 0x0C );
}

void
pcd8544::send( uint8_t data ) {

	m_data->write( DC, 0 );
	m_data->write( SCE, 0 );

	uint8_t i = 0;

	for ( ; i < 8; i++ ) {

		m_data->write( SDIN, data & ( 1 << i ) );
		m_data->write( SCLK, 1 );
		m_data->write( SCLK, 0 );
	}

	m_data->write( SCE, 1 );
}

void
pcd8544::home() {

	// Home the cursor
	cmd( HOME );

	// Update the cursor position
	m_pos[0] = m_pos[1] = 0;;
}

void
pcd8544::clear() {

	// Clear the screen
	cmd( CLEAR );

	// Update the cursor position
	m_pos[0] = m_pos[1] = 0;
}

void
pcd8544::move( uint8_t x, uint8_t y ) {

	// Check if position exists
	if ( x >= LCD_WIDTH || y >= LCD_HEIGHT )
		throw exception( utils::format( "(Error) `pcd8544::move`: the position (%u,%u) does not exists\n", x, y ) );

	// Update the cursor position
	m_pos[0] = x;
	m_pos[1] = y;

	// Set the position of the cursor on the display
	//cmd( DGRAM | ( pcd8544::lines[y] + x ) );
}

void
pcd8544::write( uint8_t chr ) {

}

} // End of displays namespace

} // End of main namespace

#endif
