/* 
    Title --- utils.cpp

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


#ifndef _RPI_HW_UTILS_CPP_
#define _RPI_HW_UTILS_CPP_

#include <rpi-hw/utils.hpp>
#include <rpi-hw/utils-inl.hpp>

namespace rpihw { // Begin main namespace

namespace utils { // Begin utilss namespace

std::string format( const char *format, ... ) {

	// Formatted string
	char buffer[256];

	// Initialize variable argument list
	va_list args;
	va_start( args, format );

	// Format the string
	std::vsnprintf( buffer, 256, format, args );

	// Clean variable argument list
	va_end( args );

	return std::string( buffer );
}

std::string
align( const std::string &text, size_t width, TextAlign align, bool truncate ) {

	// The aligned text
	std::string al = text;

	// Line length and number of spaces to insert at the start of line
	size_t len, spaces;

	// Start of the new line and position of the last white space
	size_t off = 0, lspace = 0;

	// Iterator
	size_t i = 0;

	// Align the text
	for ( ; i < al.length(); i++ ) {

		// Calculate the length of the line at current position
		len = i - off;

		// Check if the line has reached the maximum width
		if ( len >= width ) {

			// Break lines between words, except when a single word is longer than the width
			if ( !truncate && lspace != off ) {

				al.erase( al.begin() + lspace );
				i = lspace;
			}

			// If required, insert some white spaces to align the text
			if ( align != ALIGN_LEFT ) {

				spaces = ( width - ( i - off ) ) / align;
				al.insert( al.begin() + off, spaces, ' ' );
				i += spaces;
			}

			// Insert the new line character and update the offsets
			al.insert( al.begin() + i, '\n' );
			off = i + 1;

		// Split the line according to the new line character
		} else if ( al[i] == '\n' ) {

			// If required, insert some white spaces to align the text
			if ( align != ALIGN_LEFT ) {

				spaces = ( width - len ) / align;
				al.insert( al.begin() + off, spaces, ' ' );
				i += spaces;
			}

			// Update the offsets
			lspace = off = i + 1;

		// Store the last white space
		} else if ( al[i] == ' ' ) lspace = i;
	}

	// If required, insert some spaces to align the last line
	if ( align != ALIGN_LEFT )
		al.insert( al.begin() + off, ( width - len - 1 ) / align, ' ' );

	return al;
}

} // End of utilss namespace

} // End of main namespace

#endif
