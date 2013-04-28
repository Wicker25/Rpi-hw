/* 
    Title --- bitset.hpp

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


#ifndef _RPI_HW_BITSET_HPP_
#define _RPI_HW_BITSET_HPP_

#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>
#include <rpi-hw/math.hpp>

#include <rpi-hw/utils.hpp>

namespace rpihw { // Begin main namespace

// Class prototype
class bitset;

/*!
	@class bitset_ref
	@brief A reference to a bit.
*/
class bitset_ref {

	friend class bitset;

public:

	//! Destructor method
	virtual ~bitset_ref();

	/*!
		@brief Sets a bit value.
		@param[in] value The bit value.
		@return The reference to the bit.
	*/
	bitset_ref &operator=( bool value );
	/*!
		@brief Sets a bit value using a reference to another bit.
		@param[in] other The other reference to the bit.
		@return The reference to the bit.
	*/
	bitset_ref &operator=( const bitset_ref &other );

	//! Flips the bit value.
	bitset_ref &flip();

	//! Returns the inverse bit value.
	bool operator~() const;

	//! Converts bit value to boolean.
	operator bool() const;

private:

	//! Destructor method (private).
	bitset_ref( bitset &set, size_t index );

	//! Parent bitset instance.
	bitset *m_bitset;

	//! Bit position.
	size_t m_index;
};



/*!
	@class bitset
	@brief Dynamic set of bits.
*/
class bitset {

	//! Reference to a bit.
	typedef bitset_ref ref;

public:

	/*!
		@brief Constructor method.
		@param[in] size Number of the bits.
		@param[in] value Default value of the bits.
	*/
	bitset( size_t size, bool value = 0 );

	//! Destructor method.
	virtual ~bitset();

	/*!
		@brief Sets the value of the bits.
		@param[in] value The value of the bits.
	*/
	void set( bool value );

	/*!
		@brief Sets a bit value.
		@param[in] index The bit position.
		@param[in] value The bit value.
	*/
	void set( size_t index, bool value );

	/*!
		@brief Gets a bit value.
		@param[in] index The bit position.
		@return The bit value.
	*/
	bool get( size_t index ) const;

	/*!
		@brief Flips a bit value.
		@param[in] index The bit position.
	*/
	void flip( size_t index );

	//! Returns size of the set.
	size_t size() const;

	/*!
		@brief Resizes the set to contain `size` bits.
		@param[in] size The new size of the bitset.
	*/
	void resize( size_t size );

	/*!
		@brief Returns a reference to the bit at the `index` position.
		@param[in] index The bit position.
		@return A reference to the bit.
	*/
	ref operator[] ( size_t index );
	/*!
		@brief Returns the bit value at the `index` position.
		@param[in] index The bit position.
		@return The bit value.
	*/
	bool operator[] ( size_t index ) const;

private:

	//! Number of bits.
	size_t m_nbits;

	//! Physical size.
	size_t m_size;

	//! 8-bit array used to store the bits.
	uint8_t *m_data;
};

} // End of main namespace

#endif /* _RPI_HW_BITSET_HPP_ */
