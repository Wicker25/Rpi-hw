/* 
    Title --- utils.hpp

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


#ifndef _RPI_HW_UTILS_HPP_
#define _RPI_HW_UTILS_HPP_

#include <cstdio>
#include <cstdarg>

#include <vector>
#include <string>

namespace rpihw { // Begin main namespace

/*!
	@namespace rpihw::utils
	@brief Namespace of the utils functions.
*/

namespace utils { // Begin utils namespace

//! Type of alignment.
enum TextAlign {

	ALIGN_LEFT		= 0,
	ALIGN_CENTER	= 2,
	ALIGN_RIGHT		= 1
};

/*!
	@brief Allocates an array and initializes its elements with `value`.
	@param[in] size Size of the new array.
	@param[in] value Value of the array elements.
	@return Pointer to new array.
*/
template < typename T >
T *malloc( size_t size, T value );

/*!
	@brief Allocates an array and copies elements from another array.
	@param[in] size Size of the new array.
	@param[in] other The other array.
	@return Pointer to new array.
*/
template < typename T >
T *mcopy( size_t size, const T *other );

/*!
	@brief Allocates an array and copies elements from a vector.
	@param[in] other The other array.
	@return Pointer to new array.
*/
template < typename T >
T *mcopy( const std::vector< T > &other );

/*!
	@brief Sets array elements to `value`.
	@param[in] data Pointer to the array.
	@param[in] size Size of the array.
	@param[in] value The new value.
*/
template < typename T >
void memset( T *data, size_t size, T value );

/*!
	@brief Swaps two variables.
	@param a First variable.
	@param b Second variable.
*/
template < typename T >
void swap( T &a, T &b );


//! Returns a formatted string like `printf`.
std::string format( const char *format, ... );

/*!
	@brief Aligns a text.
	@param[in] text The string to align.
	@param[in] width The width of the text.
	@param[in] align The position of the alignment.
	@param[in] truncate If \c true, force to break the lines between letters.
	@return The aligned text.
*/
std::string align( const std::string &text, size_t width, TextAlign align = ALIGN_LEFT, bool truncate = 0 );

/*!
	@brief Copies `va_list` arguments into a vector.
	@param[in] args The `va_list` object.
	@param[in] total Number of the arguments.
	@param[in] offset Offset position of the first argument.
	@return The vector contains the arguments.
*/
template < typename T0, typename T1 >
std::vector< T0 > varg( va_list args, size_t total, size_t offset = 0 );

} // End of utils namespace

} // End of main namespace

#endif
