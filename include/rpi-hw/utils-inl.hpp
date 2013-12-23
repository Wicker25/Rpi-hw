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
	return ( buffer[ offset ] & ( 1 << index ) ) != 0;
}

template < typename T >
std::basic_string< T >
align( const std::basic_string< T > &text, size_t width, uint8_t flags ) {

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
	std::basic_string< T > result; result.reserve( std::distance( it, end ) * 2 );

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

#endif /* _RPI_HW_UTILS_INL_HPP_ */
