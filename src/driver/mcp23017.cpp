/* 
    Title --- driver/mcp23017.cpp

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


#ifndef _RPI_HW_DRIVER_MCP23017_CPP_
#define _RPI_HW_DRIVER_MCP23017_CPP_

#include <rpi-hw/driver/mcp23017.hpp>

namespace rpihw { // Begin main namespace

namespace driver { // Begin drivers namespace

mcp23017::mcp23017( const std::string &dev_path, uint8_t dev_addr )

	: mcp23x17		( dev_path )
	, m_i2c			( new driver::i2c( dev_path, dev_addr ) )
	, m_dev_addr	( dev_addr ) {

	// Initialize the expander
	init();
}

mcp23017::~mcp23017() {

	// Destroy the I2C controller
	delete m_i2c;
}

} // End of drivers namespace

} // End of main namespace

#endif /* _RPI_HW_DRIVER_MCP23017_CPP_ */
