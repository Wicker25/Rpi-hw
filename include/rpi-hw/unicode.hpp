/* 
    Title --- unicode.hpp

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


#ifndef _RPI_HW_UNICODE_HPP_
#define _RPI_HW_UNICODE_HPP_

#include <string>

#include <utf8.h>

#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>

namespace rpihw { // Begin main namespace

//! Type of the UTF-8 raw data.
typedef std::basic_string< uint8_t > utf8_raw;


/*!
	@class utf8_iterator
	@brief Unicode string iterator.
*/
class utf8_iterator {

	friend class ustring;

	template < typename T >
	friend utf8_iterator operator+( const utf8_iterator &it, T value );

	template < typename T >
	friend utf8_iterator operator-( const utf8_iterator &it, T value );

public:

	/*!
		@brief Constructor method.
		@param[in] buffer The raw data buffer.
		@param[in] it The iterator of the raw data buffer.
	*/
	utf8_iterator( const utf8_raw &buffer, utf8_raw::const_iterator it );

	/*!
		@brief Constructor method.
		@param[in] other Another unicode string iterator.
	*/
	utf8_iterator( const utf8_iterator &other );

	//! Destructor method.
	~utf8_iterator();

 	/*!
		@brief Assigns a new iterator position.
		@param[in] other Another unicode string iterator.
	*/
	utf8_iterator &operator=( const utf8_iterator &other );

 	/*!
		@brief Compares the iterator with another one.
		@param[in] other Another unicode string iterator.
	*/
	bool operator==( const utf8_iterator &other ) const;

 	/*!
		@brief Compares the iterator with another one.
		@param[in] other Another unicode string iterator.
	*/
	bool operator!=( const utf8_iterator &other ) const;

	//! Increments the iterator position.
	utf8_iterator &operator++();

	//! Increments the iterator position.
	utf8_iterator operator++( int );

	//! Decrements the iterator position.
	utf8_iterator &operator--();

	//! Decrements the iterator position.
	utf8_iterator operator--( int );

	//! Returns the unicode value of the current character.
	uint32_t operator*() const;

protected:

	//! Pointer to the raw data buffer.
	const utf8_raw *m_raw;

	//! First iterator of the raw data buffer.
	utf8_raw::const_iterator m_first;

	//! Second iterator of the raw data buffer.
	utf8_raw::const_iterator m_second;

	//! Unicode value of the current character.
	uint32_t m_value;
};


/*!
	@brief Increment an iterator with an arbitrary value.
	@param[in] it An unicode string iterator.
	@param[in] value An integer value.
*/
template < typename T >
utf8_iterator operator+( const utf8_iterator &it, T value );

/*!
	@brief Decrement an iterator with an arbitrary value.
	@param[in] it An unicode string iterator.
	@param[in] value An integer value.
*/
template < typename T >
utf8_iterator operator-( const utf8_iterator &it, T value );



/*!
	@class ustring
	@brief Unicode string (UTF-8).
*/
class ustring {

public:

	//! Iterator.
	typedef utf8_iterator const_iterator;

	//! Constructor method.
	ustring();

	/*!
		@brief Constructor method.
		@param[in] it The start iterator of the buffer.
		@param[in] end The end iterator of the buffer.
	*/
	template < typename iterator >
	ustring( iterator it, iterator end );

	/*!
		@brief Constructor method.
		@param[in] buffer Another unicode string used to initialize this object.
	*/
	ustring( const ustring &buffer );

	/*!
		@brief Constructor method.
		@param[in] buffer An ASCII string containing the text data.
	*/
	ustring( const std::string &buffer );

	/*!
		@brief Constructor method.
		@param[in] buffer A wide string containing the text data.
	*/
	ustring( const std::wstring &buffer );

	//! Destructor method.
	virtual ~ustring();

	/*!
		@brief Assigns the text data.
		@param[in] buffer Another unicode string containing the text data.
	*/
	ustring &operator=( const ustring &buffer );

	/*!
		@brief Assigns the text data.
		@param[in] buffer An ASCII string containing the text data.
	*/
	ustring &operator=( const std::string &buffer );

	/*!
		@brief Assigns the text data.
		@param[in] buffer A wide string containing the text data.
	*/
	ustring &operator=( const std::wstring &buffer );

	//! Returns an iterator pointing to the first character.
	const_iterator begin() const;

	//! Returns an iterator pointing to the text end.
	const_iterator end() const;

protected:

	//! Raw text buffer.
	std::basic_string< uint8_t > m_raw;
};

} // End of main namespace


// Include inline methods 
#include <rpi-hw/unicode-inl.hpp>

#endif /* _RPI_HW_UNICODE_HPP_ */
