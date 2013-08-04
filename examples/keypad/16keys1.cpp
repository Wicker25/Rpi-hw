/* 
    Title --- 16keys1.cpp [examples]

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

// Use the Rpi-hw namespace
using namespace rpihw;

// FIXME FIXME FIXME FIXME
// FIXME FIXME FIXME FIXME
// FIXME FIXME FIXME FIXME
// FIXME FIXME FIXME FIXME
/*
       (21, 10, 4, N)   colums = 4
            ||||
   ----------------------
   | (1)  (2)  (3)  (A) |
   |                    |
   | (4)  (5)  (6)  (B) |
   |                    |
   | (7)  (8)  (9)  (C) |
   |                    |
   | (*)  (0)  (#)  (D) |
   ----------------------
            ||||
      (22, 14, 15, 17)  rows = 4
*/

int
main( int argc, char *args[] ) {

	// Define the keymap
	std::vector< uint8_t > keymap = {

		'1', '2', '3', 'A',
		'4', '5', '6', 'B',
		'7', '8', '9', 'C',
		'*', '0', '#', 'D'
	};

	// Matrix keypad controller
	keypad::matrix dev( { 21, 10, 4 }, { 22, 14, 15, 17 }, keymap );

	// Print message
	std::cout << "State of keys:\n";

	// Main loop
	for ( ;; ) {

		// Write the buttons state
		const std::vector< uint8_t > &keystate = dev.keyState();

		std::cout << '\r';

		for ( uint8_t chr : keystate )
			std::cout << '\'' << (char) chr << "' ";

		std::cout << std::flush;

		// Wait some time
		time::msleep( 100 );
	}

	return 0;
}

