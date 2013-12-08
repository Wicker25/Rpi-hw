/* 
    Title --- driver/mcp23s08.cpp

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


#ifndef _RPI_HW_DRIVER_MCP23S17_CPP_
#define _RPI_HW_DRIVER_MCP23S17_CPP_

#include <rpi-hw/driver/mcp23s08.hpp>

namespace rpihw { // Begin main namespace

namespace driver { // Begin drivers namespace

mcp23s08::mcp23s08( const std::string &dev_path, uint8_t dev_id )

	: mcp23x08	( dev_path )
	, m_spi		( new driver::spi( dev_path, driver::spi::MODE_0, 8, 10000000 ) )
	, m_dev_id	( dev_id ) {

	// Initialize the expander
	init();
}

mcp23s08::~mcp23s08() {

	// Destroy the SPI controller
	delete m_spi;
}

void
mcp23s08::send( uint8_t reg, uint8_t data ) {

	// Build the buffer to send
	m_buffer[0] = WRITE | ( m_dev_id << 1 );
	m_buffer[1] = reg;
	m_buffer[2] = data;

	// Send data to the device
	m_spi->transfer( m_buffer, 3 );
}

uint8_t
mcp23s08::receive( uint8_t reg ) {

	// Build the buffer to send
	m_buffer[0] = READ | ( m_dev_id << 1 );
	m_buffer[1] = reg;

	// Receive data from the device
	m_spi->transfer( m_buffer, 3 );

	return m_buffer[2];
}

} // End of drivers namespace

} // End of main namespace

#endif /* _RPI_HW_DRIVER_MCP23S17_CPP_ */
