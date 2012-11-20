/* 
    Title --- thread.hpp

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


#ifndef _RPI_HW_THREAD_HPP_
#define _RPI_HW_THREAD_HPP_

#include <pthread.h>

#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>

namespace rpihw { // Begin main namespace

/* POSIX THREAD WRAPPER */
template < class T >
class thread {

public:

	// Thread function type
	typedef void (T::*Method)();

	// Constructor and destructor methods
	thread( T &object, Method method );
	virtual ~thread();

	// Starts thread function
	static void *do_work( void *data );

private:

	// POSIX thread
	pthread_t m_pthread;

	// Instance and method used for the thread
	T *m_object;
	Method m_method;
};

} // End of main namespace

#endif
