/* 
    Title --- bitset.hpp

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


#ifndef _RPI_HW_BITSET_HPP_
#define _RPI_HW_BITSET_HPP_

#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>
#include <rpi-hw/math.hpp>
#include <rpi-hw/utils.hpp>

namespace rpihw { // Begin main namespace

/* DYNAMIC BITSET */
class bitset {

	// Prototypes
	class ref;

public:

	// Constructor and destructor methods
	bitset( size_t size, bool value = 0 );
	virtual ~bitset();

	// Sets a bit value
	void set( size_t index, bool value );
	// Gets a bit value
	bool get( size_t index ) const;
	// Flips a bit value
	void flip( size_t index );

	// Returns size of the set
	size_t size() const;
	// Resizes the set to contain `size` bits
	void resize( size_t size );

	// Accessing methods to the bits
	ref operator[] ( size_t index );
	bool operator[] ( size_t index ) const;

private:

	// Number of bits and physical size
	size_t m_nbits, m_size;

	// 8-bit array used to store the bits
	uint8_t *m_data;
};


/* BIT REFERENCE */
class bitset::ref {

	friend class bitset;

public:

	// Constructor method
	virtual ~ref();

	// Assigns bit value
	ref &operator=( bool value );
	ref &operator=( const ref &other );

	// Flips bit value
	ref &flip();

	// Returns inverse bit value
	bool operator~() const;

	// Converts bit value to boolean 
	operator bool() const;

private:

	// Destructor method
	ref( bitset &set, size_t index );

	// Parent bitset instance
	bitset *m_bitset;

	// Bit position
	size_t m_index;
};

} // End of main namespace

#endif
