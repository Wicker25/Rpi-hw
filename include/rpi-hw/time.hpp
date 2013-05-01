/* 
    Title --- time.hpp

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


#ifndef _RPI_HW_TIME_HPP_
#define _RPI_HW_TIME_HPP_

#include <unistd.h>
#include <ctime>

namespace rpihw { // Begin main namespace

/*!
	@namespace rpihw::time
	@brief Namespace of the time functions.
*/

namespace time { // Begin time namespace

//! Waits some seconds
void sleep( size_t seconds );
//! Waits some milliseconds
void msleep( size_t mseconds );
//! Waits some microseconds
void usleep( size_t useconds );
//! Waits some nanoseconds
void nsleep( size_t nseconds );

} // End of time namespace

} // End of main namespace


// Include inline functions 
#include <rpi-hw/time-inl.hpp>

#endif /* _RPI_HW_TIME_HPP_ */
