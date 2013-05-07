/* 
    Title --- utils-inl.hpp

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


#ifndef _RPI_HW_UTILS_INL_HPP_
#define _RPI_HW_UTILS_INL_HPP_

namespace rpihw { // Begin main namespace

namespace utils { // Begin utilss namespace

template < typename T >
inline void
set_bit( T &buffer, size_t offset, uint8_t index, bool value ) {

	// Set the bit
	if ( value )
		buffer[ offset ] |= ( 1 << index );
	else
		buffer[ offset ] &= ~( 1 << index );
}

template < typename T >
inline void
clear_bit( T &buffer, size_t offset, uint8_t index ) {

	// Clear the bit
	buffer[ offset ] &= ~( 1 << index );
}

template < typename T >
inline void
flip_bit( T &buffer, size_t offset, uint8_t index ) {

	// Flip the bit value
	buffer[ offset ] ^= ( 1 << index );
}

template < typename T >
inline bool
get_bit( T &buffer, size_t offset, uint8_t index ) {

	// Return the bit value
	return (bool) ( buffer[ offset ] & ( 1 << index ) & 1 );
}

} // End of utilss namespace

} // End of main namespace

#endif /* _RPI_HW_UTILS_INL_HPP_ */
