/* 
	Title --- display/pcd8544_spi.cpp

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


#ifndef _RPI_HW_DISPLAY_PCD8544_SPI_CPP_
#define _RPI_HW_DISPLAY_PCD8544_SPI_CPP_

#include <rpi-hw/display/pcd8544-spi.hpp>

namespace rpihw { // Begin main namespace

namespace display { // Begin displays namespace

pcd8544_spi::pcd8544_spi( const std::string &dev_path, uint8_t dc, uint8_t rst )

	: pcd8544_skeleton	( { dc, rst } )
	, m_spi				( new iface::spi( dev_path, iface::spi::MODE_0, 8, 4000000 ) ) {

}

pcd8544_spi::~pcd8544_spi() {

}

void
pcd8544_spi::cmd( uint8_t data ) {

	// Set DC value to low
	m_control->write( DC, 0 );

	// Send the command to the display
	m_spi->transfer( &data, 1 );
}

void
pcd8544_spi::sendData( uint8_t data ) {

	// Set DC value to high
	m_control->write( DC, 1 );

	// Send the data to the display
	m_spi->transfer( &data, 1 );
}

} // End of displays namespace

} // End of main namespace

#endif /* _RPI_HW_DISPLAY_PCD8544_SPI_CPP_ */
