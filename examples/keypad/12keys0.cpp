/* 
    Title --- 12keys0.cpp [examples]

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


#include <iostream>

// Include Rpi-hw headers
#include <rpi-hw.hpp>
#include <rpi-hw/time.hpp>
#include <rpi-hw/keypad/matrix.hpp>

// Use Rpi-hw namespace
using namespace rpihw;

/*
      (21, 10, 4)     colums = 3
          |||
   -----------------
   | (1)  (2)  (3) |
   |               |
   | (4)  (5)  (6) |
   |               |
   | (7)  (8)  (9) |
   |               |
   | (*)  (0)  (#) |
   -----------------
          ||||
    (22, 14, 15, 17)  rows = 4
*/

int
main( int argc, char *args[] ) {

	// Matrix keypad controller
	keypad::matrix dev( { 21, 10, 4 }, { 22, 14, 15, 17 } );

	// Main loop
	for ( ;; ) {

		// Check some buttons state
		if ( dev.pressed(0) )
			std::cout << "You have pressed button 0!\n";

		if ( dev.released(2) )
			std::cout << "You have released button 2!\n";

		if ( dev.pressed(1) && dev.pressed(4) )
			std::cout << "You have pressed buttons 1 and 4!\n";

		// Wait some time
		time::msleep( 100 );
	}

   return 0;
}

