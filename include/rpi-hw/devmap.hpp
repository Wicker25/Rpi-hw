/* 
	Title --- devmap.hpp

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


#ifndef _RPI_HW_DEVMAP_HPP_
#define _RPI_HW_DEVMAP_HPP_

#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#include <rpi-hw/rpi.hpp>

#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>
#include <rpi-hw/utils.hpp>

namespace rpihw { // Begin main namespace

/*!
	@class devmap
	@brief Simple class to map devices into memory.
*/
class devmap {

public:

	/*!
		@brief Constructor method.
		@param[in] path Path to the device.
		@param[in] length Length of the mapping.
		@param[in] offset Position into the device.
	*/
	devmap( const std::string &path, size_t length, off_t offset );

	//! Destructor method.
	virtual ~devmap();

	//! Returns the address of the mapping.
	volatile uint32_t *data();

private:

	//! File descriptor of the device.
	int m_fd;

	//! Length of the mapping.
	size_t m_length;

	//! Address of the mapping.
	volatile uint32_t *m_map;
};

} // End of main namespace


// Include inline methods 
#include <rpi-hw/devmap-inl.hpp>

#endif /* _RPI_HW_DEVMAP_HPP_ */
