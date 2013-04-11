/* 
    Title --- bitset-inl.hpp

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


#ifndef _RPI_HW_BITSET_INL_HPP_
#define _RPI_HW_BITSET_INL_HPP_

namespace rpihw { // Begin main namespace

inline bitset::ref
bitset::operator[] ( size_t index ) {

	// Return bit reference at position `index`
	return ref( *this, index );
}

inline bool
bitset::operator[] ( size_t index ) const {

	// Return bit value at position `index`
	return get( index );
}

inline size_t
bitset::size() const {

	// Return the size of the set 
	return m_nbits;
}

inline bitset::ref &
bitset::ref::operator=( bool value ) {

	// Set the bit value by boolean
	m_bitset->set( m_index, value );
	return *this;
}

inline bitset::ref &
bitset::ref::operator=( const ref &other ) {

	// Set the bit value by another bit reference
	m_bitset->set( m_index, other );
	return *this;
}

inline bitset::ref &
bitset::ref::flip() {

	// Flip bit value
	m_bitset->flip( m_index );
	return *this;
}

inline bool
bitset::ref::operator~() const {

	// Return inverse bit value
	return m_bitset->get( m_index ) != true;
}

inline
bitset::ref::operator bool() const {

	// Convert bit value to boolean 
	return m_bitset->get( m_index ) != true;
}

} // End of main namespace

#endif
