/* 
    Title --- thread-inl.hpp

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


#ifndef _RPI_HW_THREAD_INL_HPP_
#define _RPI_HW_THREAD_INL_HPP_

namespace rpihw { // Begin main namespace

template < class T >
thread< T >::thread( T &object, Method method ) {

	// Store instance and method used for the thread
	m_object = &object;
	m_method = method;

	// Create the new thread
	pthread_create( &m_pthread, 0, &thread::do_work, this );
}

template < class T >
thread< T >::~thread() {

	// Destroy the thread
	pthread_join( m_pthread, 0 );
}

template < class T >
void *
thread< T >::do_work( void *data ) {

	// Get instance of the thread
	thread *self = (thread *) data;

	// Start the thread function
	(self->m_object->*self->m_method)();

	return NULL;
}

} // End of main namespace

#endif /* _RPI_HW_THREAD_INL_HPP_ */
