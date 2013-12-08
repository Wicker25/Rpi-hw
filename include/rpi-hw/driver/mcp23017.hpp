/* 
	Title --- driver/mcp23017.hpp

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


#ifndef _RPI_HW_DRIVER_MCP23017_HPP_
#define _RPI_HW_DRIVER_MCP23017_HPP_

#include <rpi-hw/rpi.hpp>

#include <rpi-hw/consts.hpp>
#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>
#include <rpi-hw/utils.hpp>

#include <rpi-hw/driver/i2c.hpp>
#include <rpi-hw/driver/mcp23x17.hpp>

namespace rpihw { // Begin main namespace

namespace driver { // Begin drivers namespace

/*!
	@class mcp23017
	@brief 16-bit I/O Expander with I2C.

	@example driver/mcp23017.cpp
*/
class mcp23017 : public mcp23x17 {

public:

	/*!
		@brief Constructor method.
		@param[in] dev_path The device path.
		@param[in] dev_addr The device address.
	*/
	mcp23017( const std::string &dev_path, uint8_t dev_addr );

	//! Destructor method.
	virtual ~mcp23017();

private:

	//! Inter Integrated Circuit.
	driver::i2c *m_i2c;

	//! Device address.
	uint8_t m_dev_addr;

	//! Sends data to the device.
	virtual void send( uint8_t reg, uint8_t data );

	//! Receives data from the device.
	virtual uint8_t receive( uint8_t reg );
};

} // End of drivers namespace

} // End of main namespace


// Include inline methods 
#include <rpi-hw/driver/mcp23017-inl.hpp>

#endif /* _RPI_HW_DRIVER_MCP23017_HPP_ */
