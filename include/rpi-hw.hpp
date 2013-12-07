/* 
    Title --- rpi-hw.hpp [main]

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


#ifndef _RPI_HW_HPP_
#define _RPI_HW_HPP_

/*!

@mainpage Reference Manual

<a href="http://hackyourmind.org/projects/rpi-hw">Rpi-hw</a> (short for "Raspberry Pi Hardware") is a free C++ library 
designed to manage the Raspberry Pi's GPIO connector and its other buses.
It allows you to connect several devices to the board (including displays, keypads, stepper motors, and sensors) as you would with Arduino's libraries.

@section features Features

@li Low-level access to the GPIO Connector and SPI, I2C, UART buses
@li High-level input/output interfaces
@li Support for I/O expander ICs
@li Support for many devices, including displays, keypads, stepper motors, and sensors (see "List of supported devices" section)
@li Unicode support (built-in)
@li Support for standard fonts (using FreeType) (optional)
@li Support for multiple image formats (using Magick++ API) (optional)
@li Drawing functions

@section list_of_supported_devices List of supported devices

@li 16 bit I/O expander with I2C (MCP23017)
@li 16 bit I/O expander with SPI (MCP23S17)
@li Character LCDs (Hitachi HD44780)
@li Graphical LCDs (Philips PCD8544)
@li Single and multiple 7-segments diplays
@li Matrix keypads
@li Ultrasonic distance sensor (HC-SR04)
@li Stepper motors

@section to_do_list To-do list

@li Support for UART interface
@li Support for 8 bit I/O expander with SPI/I2C interface

@section code_examples Code examples

Accessing to the GPIO connector:

@code{.cpp}
// Get the GPIO controller
gpio &io = gpio::get();

// Set the mode of GPIO #11
io.setup( 25, OUTPUT );

// Write on GPIO #11
io.write( 25, HIGH );
@endcode

Reading from 16-keys keypad:

@code{.cpp}
// Define the keymap
std::vector< uint8_t > keymap = {

	'1', '2', '3', 'A',
	'4', '5', '6', 'B',
	'7', '8', '9', 'C',
	'*', '0', '#', 'D'
};

// Matrix keypad controller
keypad::matrix dev( { 14, 15, 18, 23 }, { 24, 25, 8, 7 }, keymap );

// Main loop
for ( ;; ) {

    // Check the button state
    if ( dev.keyPressed('2') || dev.keyPressed('3') )
        std::cout << "You have pressed keys '2' or '3'!\n";

	// Wait some time
	time::msleep( 100 );
}
@endcode

Writing texts on a Hitachi HD44780-based LCD:

@code{.cpp}
// Display controller
display::hd44780 dev( 14, 18, 4, 17, 21, 22 );

// Initialize the 16x2 display
dev.init( 16, 2 );

// Move the cursor position
dev.move( 2, 0 );

// Write a string at cursor position
dev.write( "Hello World!" );
@endcode

@section documentation Documentation

Detailed documentation of Rpi-hw's features and usage can be found on the <a href="https://github.com/Wicker25/Rpi-hw/wiki">official wiki</a>.

@li <a href="https://github.com/Wicker25/Rpi-hw/wiki/Download%20and%20install">Download and install</a>
@li <a href="https://github.com/Wicker25/Rpi-hw/wiki/Getting%20started">Getting started</a>
@li <a href="http://hackyourmind.org/rpi-hw/">Reference manual</a>

Also you can find <a href="http://hackyourmind.org/tag/rpi-hw">some articles</a> about the library on <a href="http://hackyourmind.org/">http://hackyourmind.org/</a>.

@section license License

The library is released under terms of the <a href="http://en.wikipedia.org/wiki/GNU_Lesser_General_Public_License">GNU LGPL v3</a>.

@verbatim
Rpi-hw is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation version 3 of the License.

Rpi-hw is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.
@endverbatim

See COPYING file for more details.

@section bug_tracker Bug tracker

Have a bug? Please create an issue on GitHub at <a href="https://github.com/Wicker25/Rpi-hw/issues">https://github.com/Wicker25/Rpi-hw/issues</a>.

*/

/*!
	@namespace rpihw
	@brief Main namespace of the library.
*/

// Includes some Rpi-hw header files
#include <rpi-hw/rpi.hpp>
#include <rpi-hw/config.hpp>
#include <rpi-hw/version.hpp>
#include <rpi-hw/types.hpp>

#endif /* _RPI_HW_HPP_ */
