/* 
    Title --- bitset.cpp

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


#ifndef _RPI_HW_BITSET_CPP_
#define _RPI_HW_BITSET_CPP_

#include <rpi-hw/bitset.hpp>

#include <rpi-hw/utils.hpp>
#include <rpi-hw/utils-inl.hpp>

#include <rpi-hw/bitset-inl.hpp>

namespace rpihw { // Begin main namespace

bitset::bitset( size_t size, bool init ) {

	// Allocate memory to store the bits
	m_nbits = size;
	m_size = (size_t) math::ceil( (float) size / 8.0 );
	m_data = utils::malloc< uint8_t >( m_size, 0xFF );
}

bitset::~bitset() {

	// Free mallocated memory
	delete[] m_data;
}

void
bitset::set( size_t index, bool value ) {

	// Checks if the bit exists
	if ( index >= m_nbits )
		throw exception( utils::format( "(Error) `bitset::set`: set %p has only %lu bits\n",
										this, (unsigned long) m_nbits ) );

	// Sets value of the bit at position `index`
	uint8_t shift = index % 8;
	uint8_t &data = *( m_data + index / 8 );
	data = ( data & ~( 1 << shift ) ) | ( value << shift );
}

bool
bitset::get( size_t index ) const {

	// Checks if the bit exists
	if ( index >= m_nbits )
		throw exception( utils::format( "(Error) `bitset::get`: set %p has only %lu bits\n",
										this, (unsigned long) m_nbits ) );

	// Gets value of the bit at position `index`
	return ( *( m_data + index / 8 ) & ( 1 << ( index % 8 ) ) ) != 0;
}

void
bitset::flip( size_t index ) {

	// Checks if the bit exists
	if ( index >= m_nbits )
		throw exception( utils::format( "(Error) `bitset::flip`: set %p has only %lu bits\n",
										this, (unsigned long) m_nbits ) );

	// Flips value of the bit
	*( m_data + index / 8 ) ^= ( 1 << ( index % 8 ) );
}

void
bitset::resize( size_t size ) {

	// Remallocate the memory to store the bits
	m_nbits = size;
	m_size = (size_t) math::ceil( (float) size / 8.0 );

	delete[] m_data;
	m_data = new uint8_t[ m_size ];
}

bitset::ref::ref( bitset &set, size_t index ) {

	// Store data of parent bitset
	m_bitset = &set;
	m_index = index;
}

bitset::ref::~ref() {

}

} // End of main namespace

#endif
