/* 
    Title --- driver/mcp23017-inl.hpp

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


#ifndef _RPI_HW_DRIVER_MCP23017_INL_HPP_
#define _RPI_HW_DRIVER_MCP23017_INL_HPP_

namespace rpihw { // Begin main namespace

namespace driver { // Begin drivers namespace

inline void
mcp23017::send( uint8_t reg, uint8_t data ) {

	// Send data to the device
	m_i2c->writeReg8( reg, data );
}

inline uint8_t
mcp23017::receive( uint8_t reg ) {

	// Receive data from the device
	return m_i2c->readReg8( reg );
}

} // End of drivers namespace

} // End of main namespace

#endif /* _RPI_HW_DRIVER_MCP23017_INL_HPP_ */
