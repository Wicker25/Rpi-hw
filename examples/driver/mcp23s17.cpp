/* 
    Title --- mcp23s17.cpp [examples]

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
#include <rpi-hw/time.hpp>

#include <rpi-hw/driver/mcp23s17.hpp>
#include <rpi-hw/gpio.hpp>

// Use Rpi-hw namespace
using namespace rpihw;

int
main( int argc, char *args[] ) {

	// Create the 16-bit I/O expander
	driver::mcp23s17 expander( "/dev/spidev0.0", 0 );

	// Get the GPIO controller
	gpio &io = gpio::get();

	// Add the I/O expander to the standard GPIO connector
	io.expand( 100, expander );

	// Set new GPIOs as output pin
	for ( int i = 0; i < 16; ++i )
		io.setup( 100 + i, OUTPUT ); 


	// Animate LEDs :)
	size_t time = 0;

	for ( ;; ) {

		// Turn on the current pin
		io.write( 100 + time % 16, HIGH );

		// Wait some time
		time::msleep(100);

		// Turn off the current pin
		io.write( 100 + time % 16, LOW );

		++time;
	}

	return 0;
}
