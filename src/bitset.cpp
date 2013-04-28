/* 
    Title --- bitset.cpp

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


#ifndef _RPI_HW_BITSET_CPP_
#define _RPI_HW_BITSET_CPP_

#include <rpi-hw/bitset.hpp>

#include <rpi-hw/utils.hpp>
#include <rpi-hw/utils-inl.hpp>

#include <rpi-hw/bitset-inl.hpp>

namespace rpihw { // Begin main namespace

bitset_ref::bitset_ref( bitset &set, size_t index ) {

	// Store data of parent bitset
	m_bitset = &set;
	m_index = index;
}

bitset_ref::~bitset_ref() {

}



bitset::bitset( size_t size, bool init ) {

	// Allocate memory to store the bits
	m_nbits	= size;
	m_size	= (size_t) math::ceil( (float) size / 8.0 );
	m_data	= utils::malloc< uint8_t >( m_size, 0xFF * (uint8_t) init );
}

bitset::~bitset() {

	// Free allocated memory
	delete[] m_data;
}

void
bitset::set( bool value ) {

	// Set the value of the bits
	utils::memset< uint8_t >( m_data, m_size, 0xFF * (uint8_t) value );
}

void
bitset::set( size_t index, bool value ) {

	// Check if the bit exists
	if ( index >= m_nbits )
		throw exception( utils::format( "(Error) `bitset::set`: set has only %lu bits\n", (unsigned long) m_nbits ) );

	// Calculate the bit position
	uint8_t shift = (uint8_t) ( index % 8 );

	// Get the block of the bits
	uint8_t &block = *( m_data + index / 8 );

	// Set the value of the bit at position `index`
	if ( value )
		block |= ( 1 << shift );
	else
		block &= ~( 1 << shift );
}

bool
bitset::get( size_t index ) const {

	// Check if the bit exists
	if ( index >= m_nbits )
		throw exception( utils::format( "(Error) `bitset::get`: set has only %lu bits\n", (unsigned long) m_nbits ) );

	// Get the value of the bit at position `index`
	return ( *( m_data + index / 8 ) & ( 1 << ( index % 8 ) ) ) != 0;
}

void
bitset::flip( size_t index ) {

	// Check if the bit exists
	if ( index >= m_nbits )
		throw exception( utils::format( "(Error) `bitset::flip`: set has only %lu bits\n", (unsigned long) m_nbits ) );

	// Flip the value of the bit
	*( m_data + index / 8 ) ^= ( 1 << ( index % 8 ) );
}

void
bitset::resize( size_t size ) {

	// Reallocate the memory to store the bits
	m_nbits = size;
	m_size = (size_t) math::ceil( (float) size / 8.0 );

	delete[] m_data;
	m_data = new uint8_t[ m_size ];
}

} // End of main namespace

#endif /* _RPI_HW_BITSET_CPP_ */
