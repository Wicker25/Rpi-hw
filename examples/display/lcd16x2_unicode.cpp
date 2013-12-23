/* 
    Title --- lcd16x2_unicode.cpp [examples]

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


// Include Rpi-hw headers
#include <rpi-hw.hpp>
#include <rpi-hw/display/hd44780.hpp>

// Use Rpi-hw namespace
using namespace rpihw;

int
main( int argc, char *args[] ) {

	// Create the display controller
	display::hd44780 dev( 14, 18, 4, 17, 21, 22 );

	// Initialize the 16x2 display
	dev.init( 16, 2, display::hd44780::ROM_A00 );

	// Write a string at cursor position
	dev.write( U"ハローワールト゜" );

	return 0;
}

