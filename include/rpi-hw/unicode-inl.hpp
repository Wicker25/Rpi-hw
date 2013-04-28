/* 
    Title --- unicode-inl.hpp

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


#ifndef _RPI_HW_UNICODE_INL_HPP_
#define _RPI_HW_UNICODE_INL_HPP_

namespace rpihw { // Begin main namespace

inline utf8_iterator &
utf8_iterator::operator=( const utf8_iterator &other ) {

	// Assign a new iterator position
	m_raw		= other.m_raw;
	m_first		= other.m_first;
	m_second	= other.m_second;
	m_value		= other.m_value;

	return *this;
}

inline bool
utf8_iterator::operator==( const utf8_iterator &other ) const {

	// Compare the iterator with another one
	return m_first == other.m_first;
}

inline bool
utf8_iterator::operator!=( const utf8_iterator &other ) const {

	// Compare the iterator with another one
	return m_first != other.m_first;
}


inline utf8_iterator &
utf8_iterator::operator++() {

	// Increment the iterator position
	m_first = m_second;

	if ( m_first != m_raw->end() )
		m_value = utf8::next( m_second, m_raw->end() );

	return *this;
}

inline utf8_iterator
utf8_iterator::operator++( int ) {

	// Increment the iterator position
	utf8_iterator tmp( *this );
	++(*this);
	return tmp;
}

inline utf8_iterator &
utf8_iterator::operator--() {

	// Decrement the iterator position
	m_second = m_first;

	if ( m_second != m_raw->begin() )
		m_value = utf8::previous( m_first, m_raw->begin() );

	return *this;
}

inline utf8_iterator
utf8_iterator::operator--( int ) {

	// Decrement the iterator position
	utf8_iterator tmp( *this );
	--(*this);
	return tmp;
}

inline uint32_t
utf8_iterator::operator*() const {

	// Return the unicode value of the current character.
	return m_value;
}

template < typename T >
inline utf8_iterator
operator+( const utf8_iterator &it, T value ) {

	//! Increment the iterator with the arbitrary value
	return utf8_iterator( *it.m_raw, it.m_first + value );
}

template < typename T >
inline utf8_iterator
operator-( const utf8_iterator &it, T value ) {

	//! Decrement the iterator with the arbitrary value
	return utf8_iterator( *it.m_raw, it.m_first - value );
}



inline ustring &
ustring::operator=( const ustring &buffer ) {

	// Update the text buffer
	m_raw.assign( buffer.m_raw.begin(), buffer.m_raw.end() );
	return *this;
}

inline ustring &
ustring::operator=( const std::string &buffer ) {

	// Update the text buffer
	m_raw.assign( buffer.begin(), buffer.end() );
	return *this;
}

inline ustring &
ustring::operator=( const std::wstring &buffer ) {

	// Update the text buffer
	if ( sizeof( wchar_t ) == 32 )
		utf8::utf32to8( buffer.begin(), buffer.end(), std::back_inserter( m_raw ) );

	else if( sizeof( wchar_t ) == 16 )
		utf8::utf16to8( buffer.begin(), buffer.end(), std::back_inserter( m_raw ) );

	return *this;
}

inline ustring::const_iterator
ustring::begin() const {

	//! Returns an iterator pointing to the first character
	return ustring::const_iterator( m_raw, m_raw.begin() );
}

inline ustring::const_iterator
ustring::end() const {

	// Returns an iterator pointing to the text end
	return ustring::const_iterator( m_raw, m_raw.end() );
}

} // End of main namespace

#endif /* _RPI_HW_UNICODE_INL_HPP_ */
