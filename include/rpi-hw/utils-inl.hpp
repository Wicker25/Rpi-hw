/* 
    Title --- utils-inl.hpp

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


#ifndef _RPI_HW_UTILS_INL_HPP_
#define _RPI_HW_UTILS_INL_HPP_

namespace rpihw { // Begin main namespace

namespace utils { // Begin utilss namespace

template < typename T >
T *
malloc( size_t size, T value ) {

	// Create the new array
	T *data = new T[ size ];

	// Initialize the elements
	memset< T >( data, size, value );

	return data;
}

template < typename T >
T *
malloc( size_t size, const  T *other ) {

	// Create the new array
	T *data = new T[ size ];

	// Initialize the elements
	size_t i = 0;

	for ( ; i < size; i++ ) data[i] = other[i];

	return data;
}

template < typename T >
inline T *
malloc( const std::vector< T > &other ) {

	// Allocate and initialize a new array
	return malloc( other.size(), &other[0] );
}

template < typename T >
void
memset( T *data, size_t size, T value ) {

	// Set the elements of an array
	size_t i = 0;

	for ( ; i < size; i++ ) data[i] = value;
}

inline void
sleep( size_t seconds ) {

	// Wait some seconds
	::usleep( (useconds_t) ( seconds * 1000000 ) );
}

inline void
msleep( size_t mseconds ) {

	// Wait some milliseconds
	::usleep( (useconds_t) ( mseconds * 1000 ) );
}

inline void
usleep( size_t useconds ) {

	// Wait some microseconds
	::usleep( (useconds_t) useconds );
}

template < typename T0, typename T1 >
std::vector< T0 >
varg( va_list args, size_t total, size_t offset ) {

	// Vector of arguments
	std::vector< T0 > vec;

	T0 value;
	total += offset;

	// Copy `va_list` arguments into the vector
	size_t i = 0;

	for ( ; i < total; i++ ) {

		value = (T0) va_arg( args, T1 );
		if ( i >= offset ) vec.push_back( value );
	}

	return vec;
}

} // End of utilss namespace

} // End of main namespace

#endif
