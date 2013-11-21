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

#include <rpi-hw/types.hpp>

namespace rpihw { // Begin main namespace

/*!
	@namespace rpihw::utils
	@brief Namespace of the utils functions.
*/

namespace utils { // Begin utils namespace

//! Parameters of text.
enum TextFlags {

	ALIGN_LEFT		= 0x01,
	ALIGN_CENTER	= 0x02,
	ALIGN_RIGHT		= 0x04,
	WORD_WRAP		= 0x08,
	WORD_BREAK		= 0x10
};


/*!
	@brief Sets a bit in a variable.
	@param[in] buffer The buffer containing the data.
	@param[in] offset The offset position in the buffer.
	@param[in] index The bit position.
	@param[in] value The bit value.
*/
template < typename T >
void set_bit( T &buffer, size_t offset, uint8_t index, bool value = 1 );

/*!
	@brief Clears a bit in a variable.
	@param[in] buffer The buffer containing the data.
	@param[in] offset The offset position in the buffer.
	@param[in] index The bit position.
*/
template < typename T >
void clear_bit( T &buffer, size_t offset, uint8_t index );

/*!
	@brief Flips a bit value in a variable.
	@param[in] buffer The buffer containing the data.
	@param[in] offset The offset position in the buffer.
	@param[in] index The bit position.
*/
template < typename T >
void flip_bit( T &buffer, size_t offset, uint8_t index );

/*!
	@brief Retuns a bit value in a variable.
	@param[in] buffer The buffer containing the data.
	@param[in] offset The offset position in the buffer.
	@param[in] index The bit position.
	@return The bit value.
*/
template < typename T >
bool get_bit( T &buffer, size_t offset, uint8_t index );


//! Returns a formatted string like `printf`.
std::string format( const char *format, ... );

/*!
	@brief Aligns a text.
	@param[in] text The string to align.
	@param[in] width The width of the text.
	@param[in] flags The parameters of the text.
	@return The aligned text.
*/
std::string align( const std::string &text, size_t width, uint8_t flags = ALIGN_LEFT );

} // End of utils namespace

} // End of main namespace


// Include inline methods 
#include <rpi-hw/utils-inl.hpp>

#endif /* _RPI_HW_UTILS_HPP_ */
