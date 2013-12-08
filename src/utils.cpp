/* 
    Title --- utils.cpp

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


#ifndef _RPI_HW_UTILS_CPP_
#define _RPI_HW_UTILS_CPP_

#include <rpi-hw/utils.hpp>

namespace rpihw { // Begin main namespace

namespace utils { // Begin utils namespace

std::string format( const char *format, ... ) {

	// Formatted string
	char buffer[256];

	// Format the string
	va_list args;
	va_start( args, format );

	std::vsnprintf( buffer, 256, format, args );

	va_end( args );

	return std::string( buffer );
}

std::string
align( const std::string &text, size_t width, uint8_t flags ) {

	// Get the word wrapping mode
	bool word_break = flags & WORD_BREAK;

	// Calculate the margin factor
	size_t margin = 0;

	if ( flags & ALIGN_CENTER )
		margin = 2;
	else if ( flags & ALIGN_RIGHT )
		margin = 1;

	// Iterators
	auto it = std::begin( text ), end = std::end( text );

	// The aligned string
	std::string result; result.reserve( std::distance( it, end ) * 2 );

	// Start of the current line
	auto off = it;

	// Current line width
	size_t line_len = 0;


	// Break lines between characters
	if ( word_break ) {

		for ( ; it != end; ++it ) {

			line_len++;

			if ( *it == '\n' ) {

				if ( margin )
					result.append( ( width - line_len + 1 ) / margin, ' ' );

				result.append( off, it );
				result.push_back( '\n' );

				off = it + 1;
				line_len = 0;

			} else if ( line_len > width ) {

				if ( margin )
					result.append( ( width - line_len + 1 ) / margin, ' ' );

				result.append( off, it );
				result.push_back( '\n' );

				off = it;
				line_len = 1;
			}
		}

		// Append the last line
		if ( margin )
			result.append( ( width - line_len ) / margin, ' ' );

		result.append( off, end );


	// Break lines between words, except when a single word is longer than the width
	} else {

		// Start of the current word
		auto word_start = it;

		// Current word width
		size_t word_len = 0;

		for ( ; it != end; ++it ) {

			++word_len;

			if ( line_len + word_len > width ) {

				if ( off == word_start ) {

					if ( margin )
						result.append( ( width - ( line_len + word_len ) + 1 ) / margin, ' ' );

					result.append( off, it );
					result.push_back( '\n' );

					off = word_start = it;
					line_len = 0;
					word_len = 1;

				} else {

					if ( margin )
						result.append( ( width - line_len + 1 ) / margin, ' ' );

					result.append( off, word_start );
					result.push_back( '\n' );

					off = ++word_start;
					line_len = 0;
				}
			}

			if ( *it == '\n' ) {

				if ( margin )
					result.append( ( width - ( line_len + word_len ) + 1 ) / margin, ' ' );

				result.append( off, it );
				result.push_back( '\n' );

				off = word_start = it + 1;
				line_len = word_len = 0;

			} else if ( *it == ' ' ) {

				word_start = it;

				line_len += word_len;
				word_len = 0;
			}
		}

		// Append the last line
		if ( margin )
			result.append( ( width - ( line_len + word_len ) ) / margin, ' ' );

		result.append( off, end );
	}

	return result;
}

} // End of utilss namespace

} // End of main namespace

#endif /* _RPI_HW_UTILS_CPP_ */
