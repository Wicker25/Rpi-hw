/* 
	Title --- display/pcd8544-skeleton.cpp

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


#ifndef _RPI_HW_DISPLAY_PCD8544_SKELETON_CPP_
#define _RPI_HW_DISPLAY_PCD8544_SKELETON_CPP_

#include <rpi-hw/display/pcd8544-skeleton.hpp>

namespace rpihw { // Begin main namespace

namespace display { // Begin displays namespace

pcd8544_skeleton::pcd8544_skeleton( std::initializer_list< uint8_t > pins )

	: designer< int8_t, bool, 1 >	( LCD_WIDTH, LCD_HEIGHT )
	, m_control						( new iface::output( pins ) )
	, m_buffer						( DDRAM_SIZE, 0x00 )
	, m_updates						( DDRAM_SIZE, true ) {

	// Set the foreground color
	setColor( COLOR_BLACK );
}

pcd8544_skeleton::~pcd8544_skeleton() {

}

void
pcd8544_skeleton::init( uint8_t contrast, bool inverse ) {

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
pcd8544_skeleton::setContrast( uint8_t value ) {

	// Set the contrast of the display
	cmd( FUNC | FUNC_H );
	cmd( VOP | ( value & 0x7f ) );
	cmd( FUNC );
}

void
pcd8544_skeleton::drawPixel( int8_t x, int8_t y, color_iterator< bool > color ) {

	// Check if positions exist
	if ( x < 0 || y < 0 || x >= LCD_WIDTH || y >= LCD_HEIGHT )
		return;

	// Calculate the bit position
	uint8_t index = (uint8_t) y % 8;

	// Get the block containing the pixel
	size_t block = (size_t) x + (size_t) y / 8 * LCD_WIDTH;

	// Set the color of the pixel
	utils::set_bit( m_buffer, block, index, *color == false );

	// Add the update to the buffer
	m_updates[ block ] = true;
}

bool
pcd8544_skeleton::getPixel( int8_t x, int8_t y ) const {

	// Check if position exists 
	if ( x < 0 || y < 0 || x >= LCD_WIDTH || y >= LCD_HEIGHT )
		return 0;

	// Get the block containing the pixel
	size_t block = (size_t) x + ( (size_t) y / 8 ) * LCD_WIDTH;

	// Return the color of the pixel
	return utils::get_bit( m_buffer, block, 7 - ( y % 8 ) );
}

uint16_t
pcd8544_skeleton::redraw() {

	// Number of updated blocks
	uint16_t total = 0;

	// Flag indicating that a block is skipped
	bool jump = true;

	// Iterators
	uint16_t k = 0; uint8_t i, j;

	// Update the pixels in the bounding box
	for ( j = 0; j < DDRAM_HEIGHT; ++j ) {

		cmd( YADDR | j );

		for ( i = 0; i < DDRAM_WIDTH; ++i, ++k ) {

			if ( m_updates[k] ) {

				if ( jump ) {

					cmd( XADDR | i );
					jump = false;
				}

				sendData( m_buffer[ k ] );
				total++;

			} else jump = true;
		}
	}

	// Remove all updates from the buffer
	m_updates.assign( DDRAM_SIZE, false );

	// Return the number of updated blocks
	return total;
}

void
pcd8544_skeleton::clear() {

	// Clear the data buffer
	m_buffer.assign( DDRAM_SIZE, 0x00 );

	// Add the update to the buffer
	m_updates.assign( DDRAM_SIZE, true );

	// Restore the cursor position
	setPenPosition( 0, 0 );
}

} // End of displays namespace

} // End of main namespace

#endif /* _RPI_HW_DISPLAY_PCD8544_SKELETON_CPP_ */
