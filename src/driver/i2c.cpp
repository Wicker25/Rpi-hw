/* 
    Title --- driver/i2c.cpp

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


#ifndef _RPI_HW_DRIVER_I2C_CPP_
#define _RPI_HW_DRIVER_I2C_CPP_

#include <rpi-hw/driver/i2c.hpp>

namespace rpihw { // Begin main namespace

namespace driver { // Begin drivers namespace

i2c::i2c( const std::string &dev_path, uint8_t addr )

	: m_dev_path	( dev_path )
	, m_addr		( addr ) {

	// Open device file
	m_dev_fd = open( m_dev_path.c_str(), O_RDWR );

	if ( m_dev_fd < 0 )
		throw exception( utils::format( "(Fatal) `i2c`: can't open I2C device '%s'\n", strerror( errno ) ) );

	// Select slave device
	if ( ioctl( m_dev_fd, I2C_SLAVE, addr ) < 0 )
		throw exception( utils::format( "(Fatal) `i2c`: can't select slave device '%s'\n", strerror( errno ) ) );
}

i2c::~i2c() {

	// Close device file
	close( m_dev_fd );
}

} // End of drivers namespace

} // End of main namespace

#endif /* _RPI_HW_DRIVER_I2C_CPP_ */
