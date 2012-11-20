/* 
    Title --- s7seg.cpp [examples]

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


#include <iostream>
#include <ctime>

#include <rpi-hw.hpp>

#include <rpi-hw/utils.hpp>
#include <rpi-hw/utils-inl.hpp>

#include <rpi-hw/display/s7seg.hpp>
#include <rpi-hw/display/s7seg-inl.hpp>

// Use the Rpi-hw namespace
using namespace rpihw;

/*
          1
        ######
    0  #      # 4
       #  17  #
        ######
    14 #      # 18
       #      #
        ######
         15
*/

int
main( int argc, char *args[] ) {

	// Seven-segment display controller
	display::s7seg disp( 1, 4, 18, 15, 14, 0, 17 );

	// Iterator
	size_t i = 0;

	// Main loop
	while ( 1 ) {

		// Set the digit
		disp.set( i++ );

		// Wait some time
		utils::msleep( 500 );
	}

	return 0;
}

