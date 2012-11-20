/* 
    Title --- utils.hpp

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


#ifndef _RPI_HW_UTILS_HPP_
#define _RPI_HW_UTILS_HPP_

#include <cstdio>
#include <cstdarg>
#include <ctime>

#include <vector>
#include <string>

namespace rpihw { // Begin main namespace

namespace utils { // Begin utilss namespace

// Constants
enum TextAlign {

	ALIGN_LEFT		= 0,
	ALIGN_CENTER	= 2,
	ALIGN_RIGHT		= 1
};

// Allocates and initializes an array
template < typename T >
T *malloc( size_t size, T value );
template < typename T >
T *malloc( size_t size, const T *values );
template < typename T >
T *malloc( const std::vector< T > &values );

// Sets the elements of an array
template < typename T >
void memset( T *data, size_t size, T value );

// Waits some time
void sleep( size_t seconds );
void msleep( size_t mseconds );
void usleep( size_t useconds );

// Returns formatted string like `sprintf`
std::string format( const char *format, ... );

// Aligns a text (left, center, and right)
std::string align( const std::string &text, size_t width, TextAlign align = ALIGN_LEFT, bool truncate = 0 );

// Converts `va_list` to vector
template < typename T0, typename T1 >
std::vector< T0 > varg( va_list args, size_t total, size_t offset = 0 );

} // End of utilss namespace

} // End of main namespace

#endif
