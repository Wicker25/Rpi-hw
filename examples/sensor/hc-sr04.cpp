/* 
    Title --- hc-sr04.cpp [examples]

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


#include <rpi-hw.hpp>

#include <rpi-hw/utils.hpp>
#include <rpi-hw/time.hpp>
#include <rpi-hw/sensor/hc-sr04.hpp>

// Use the Rpi-hw namespace
using namespace rpihw;

int
main( int argc, char *args[] ) {

	// Create the stepper controller
	sensor::hcsr04 disp( 23, 24 );

	// Calculate the elapsed time between sending and receiving back the pulse
	double elapsed	= disp.timing();

	// Calculate the distance from the sensor to an object or surface
	double distance	= disp.ranging();

	std::cout << utils::format( "Elapsed time: %f\n", elapsed );
	std::cout << utils::format( "Distance: %.1f cm\n", distance );

	return 0;
}

