/* 
    Title --- mutex.cpp

    Copyright (C) 2012 Giacomo Trudu - wicker25[at]gmail[dot]com

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


#ifndef _RPI_HW_MUTEX_CPP_
#define _RPI_HW_MUTEX_CPP_

#include <rpi-hw/mutex.hpp>
#include <rpi-hw/mutex-inl.hpp>

namespace rpihw { // Begin main namespace

mutex::mutex() {

	// Initialize the mutex
	pthread_mutex_init( &m_pmutex, NULL );
}

mutex::~mutex() {

	// Deinitialize the mutex
	pthread_mutex_destroy( &m_pmutex );
}

} // End of main namespace

#endif