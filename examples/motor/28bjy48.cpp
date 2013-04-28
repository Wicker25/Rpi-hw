/* 
    Title --- 28bjy48.cpp [examples]

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
#include <rpi-hw/utils-inl.hpp>

#include <rpi-hw/time.hpp>
#include <rpi-hw/time-inl.hpp>

#include <rpi-hw/motor/stepper.hpp>
#include <rpi-hw/motor/stepper-inl.hpp>

// Use the Rpi-hw namespace
using namespace rpihw;

int
main( int argc, char *args[] ) {

	// Create the stepper controller
	motor::stepper disp( 4096, 24, 25, 8, 7 );

	// Start demo
	disp.setSpeed( 3.0 );
	disp.rotate( 45.0 );
	time::msleep( 500 );

	disp.setSpeed( 6.0 );
	disp.rotate( 45.0 );
	time::msleep( 500 );

	disp.setSpeed( 9.0 );
	disp.rotate( 45.0 );
	time::msleep( 500 );

	disp.setSpeed( 11.0 );
	disp.rotate( 45.0 );
	time::msleep( 500 );

	disp.setSpeed( 14.0 );
	disp.rotate( 90.0 );
	time::msleep( 500 );

	disp.setSpeed( 14.0 );
	disp.rotate( 90.0 );
	time::msleep( 500 );

	disp.setDirection( motor::DIRECTION_CCW );
	disp.rotate( 360.0 );
	time::msleep( 500 );

	return 0;
}

