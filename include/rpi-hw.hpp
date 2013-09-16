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

@section description Description

<a href="http://hackyourmind.org/projects/rpi-hw">Rpi-hw</a> is a free C++ library 
designed to manage the Raspberry Pi's General Purpose Input/Output (GPIO) connector.
The library is released under terms of the [GNU LGPL v3](http://en.wikipedia.org/wiki/GNU_Lesser_General_Public_License).

The source of the latest version of Rpi-hw is available on [github.com](https://github.com/Wicker25/Rpi-hw) at:

@li <a href="https://github.com/Wicker25/Rpi-hw">https://github.com/Wicker25/Rpi-hw</a>

@section main_features Main features

The following are some features of the library:

@li Low-level management of the GPIOs
@li Generic input/output interfaces
@li SPI support
@li Display support (7-segments, HD44780, PCD8544)
@li Keypad support (matrix keypad)
@li Sensor support (HC-SR04)
@li Stepper motor support
@li Unicode support (built-in)
@li Handles multiple image formats (using Magick++ API) (optional)
@li Supports standard fonts (using FreeType) (optional)
@li Drawing functions

@section documentation Documentation

Detailed documentation of Rpi-hw's features and usage can be found on the <a href="https://github.com/Wicker25/Rpi-hw/wiki">wiki</a>.

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
