/* 
    Title --- devmap.cpp

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


#ifndef _RPI_HW_DEVMAP_CPP_
#define _RPI_HW_DEVMAP_CPP_

#include <rpi-hw/devmap.hpp>

namespace rpihw { // Begin main namespace

devmap::devmap( const std::string &path, size_t length, off_t offset ) : m_length( length ) {

	// Open the device file
	m_dev_fd = open( path.c_str(), O_RDWR | O_SYNC );

	if ( m_dev_fd < 0 )
		throw exception( utils::format( "(Error) `devmap`: can't open `%s`, you must be 'root' to run this software!", path.c_str() ) );

	// Map the device into memory
	m_map = (volatile uint32_t *) mmap(

		0,
		m_length,
		PROT_READ | PROT_WRITE,
		MAP_SHARED,
		m_dev_fd,
		offset
	);

	// Check possible errors
	if ( m_map == MAP_FAILED )
		throw exception( utils::format( "(Error) `devmap`: mapping error at address %p (devmap)\n", m_map ) );
}

devmap::~devmap() {

	// Unmap the device
	munmap( (uint32_t *) m_map, m_length );

	// Close the device file
	close( m_dev_fd );
}

} // End of main namespace

#endif /* _RPI_HW_DEVMAP_CPP_ */
