/* 
	Title --- driver/i2c.hpp

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


#ifndef _RPI_HW_DRIVER_I2C_HPP_
#define _RPI_HW_DRIVER_I2C_HPP_

#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>

#include <rpi-hw/rpi.hpp>

#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>
#include <rpi-hw/utils.hpp>

namespace rpihw { // Begin main namespace

namespace driver { // Begin drivers namespace

/*!
	@class i2c
	@brief Inter Integrated Circuit.
*/
class i2c {

public:

	/*!
		@brief Constructor method.
		@param[in] dev_path The device path.
		@param[in] addr The I2C slave address.
	*/
	i2c( const std::string &dev_path, uint8_t addr );

	//! Destructor method.
	virtual ~i2c();

private:

	//! The device path.
	std::string m_dev_path;

	//! The I2C slave address.
	uint32_t m_addr;

	//! File descriptor of the device.
	int m_dev_fd;
};

} // End of drivers namespace

} // End of main namespace


// Include inline methods 
#include <rpi-hw/driver/i2c-inl.hpp>

#endif /* _RPI_HW_DRIVER_I2C_HPP_ */
