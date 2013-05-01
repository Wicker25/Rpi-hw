/* 
    Title --- unicode.cpp

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


#ifndef _RPI_HW_UNICODE_CPP_
#define _RPI_HW_UNICODE_CPP_

#include <rpi-hw/unicode.hpp>

namespace rpihw { // Begin main namespace

utf8_iterator::utf8_iterator( const utf8_raw &buffer, utf8_raw::const_iterator it ) : m_raw( &buffer ), m_first( it ), m_second( it ) {

	// Read the first character value
	if ( m_first != m_raw->end() )
		m_value = utf8::next( m_second, m_raw->end() );
	else
		m_value = 0;
}

utf8_iterator::utf8_iterator( const utf8_iterator &other ) : m_raw( other.m_raw ), m_first( other.m_first ), m_second( other.m_second ), m_value( other.m_value ) {

}

utf8_iterator::~utf8_iterator() {

}



ustring::ustring() {

}

ustring::ustring( const ustring &buffer ) : m_raw( buffer.m_raw.begin(), buffer.m_raw.end() ) {

}

ustring::ustring( const std::string &buffer ) {

	if ( !utf8::is_valid( buffer.begin(), buffer.end() ) )
		throw exception( "(Error) `ustring->constructor`: invalid UTF-8 string\n" );

	// Copy the text buffer
	m_raw.assign( buffer.begin(), buffer.end() );
}

ustring::ustring( const std::wstring &buffer ) {

	// Convert the text buffer
	if ( sizeof( wchar_t ) == 32 )
		utf8::utf32to8( buffer.begin(), buffer.end(), std::back_inserter( m_raw ) );

	else if( sizeof( wchar_t ) == 16 )
		utf8::utf16to8( buffer.begin(), buffer.end(), std::back_inserter( m_raw ) );
}

ustring::~ustring() {

}

} // End of main namespace

#endif /* _RPI_HW_UNICODE_CPP_ */
