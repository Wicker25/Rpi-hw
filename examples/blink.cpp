/* 
    Title --- blink.cpp [examples]

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


#include <ctime>
#include <rpi-hw.hpp>

// Use Rpi-hw namespace
using namespace rpihw;

int
main( int argc, char *args[] ) {

	// GPIO controller interface
	gpio io;

	// Set the output pin to the led
	io.setup( 11, gpio::OUTPUT );

	// Blink
	for ( ;; ) {

		// Turn it on
		io.write( 11, gpio::HIGH );

		// Wait some time
		utils::usleep( 1000000 );

		// Turn it off
		io.write( 11, gpio::LOW );

		// Wait some time
		utils::usleep( 1000000 );
	}

	return 0;
}

