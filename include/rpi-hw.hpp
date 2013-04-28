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

<a href="http://www.hackyourmind.org/blog/projects/rpi-hw/">Rpi-hw</a> is a free C++ library 
designed to manage the Raspberry Pi's General Purpose Input/Output (GPIO) connector.
The library is released under terms of the [GNU LGPL v3](http://en.wikipedia.org/wiki/GNU_Lesser_General_Public_License).

The source of the latest version of Rpi-hw is available on [github.com](https://github.com/Wicker25/Rpi-hw) at:

@li <a href="https://github.com/Wicker25/Rpi-hw">https://github.com/Wicker25/Rpi-hw</a>

@section main_features Main features

The following are some features of the library:

@li Low-level management of the GPIOs
@li Generic input/output interfaces
@li Displays support (7-segments, HD44780, PCD8544)
@li Keypad support (matrix keypad)
@li Stepper motor support
@li Unicode support (using UTF8-CPP) (built-in)
@li Handles multiple image formats (using Magick++ API) (optional)
@li Supports standard fonts (using FreeType) (optional)
@li Drawing functions

@section documentation Documentation

Detailed documentation of Rpi-hw's features and usage can be found on the <a href="https://github.com/Wicker25/Rpi-hw/wiki">wiki</a>.

*/

/*!
	@namespace rpihw
	@brief Main namespace of the library.
*/

// Includes all Rpi-hw header files
#include <rpi-hw/rpi.hpp>
#include <rpi-hw/config.hpp>

#include <rpi-hw/version.hpp>
#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>

#include <rpi-hw/math.hpp>

#include <rpi-hw/utils.hpp>
#include <rpi-hw/utils-inl.hpp>

#include <rpi-hw/time.hpp>
#include <rpi-hw/time-inl.hpp>

#include <rpi-hw/mutex.hpp>
#include <rpi-hw/mutex-inl.hpp>

#include <rpi-hw/thread.hpp>
#include <rpi-hw/thread-inl.hpp>

#include <rpi-hw/gpio.hpp>
#include <rpi-hw/gpio-inl.hpp>

#include <rpi-hw/bitset.hpp>
#include <rpi-hw/bitset-inl.hpp>

#include <rpi-hw/unicode.hpp>
#include <rpi-hw/unicode-inl.hpp>

#include <rpi-hw/iface/base.hpp>
#include <rpi-hw/iface/base-inl.hpp>

#include <rpi-hw/iface/output.hpp>
#include <rpi-hw/iface/output-inl.hpp>

#include <rpi-hw/iface/input.hpp>
#include <rpi-hw/iface/input-inl.hpp>

#include <rpi-hw/iface/shift-base.hpp>
#include <rpi-hw/iface/shift-base-inl.hpp>

#include <rpi-hw/iface/shift-out.hpp>
#include <rpi-hw/iface/shift-out-inl.hpp>

#include <rpi-hw/iface/shift-in.hpp>
#include <rpi-hw/iface/shift-in-inl.hpp>

#include <rpi-hw/iface/encoder-out.hpp>
#include <rpi-hw/iface/encoder-out-inl.hpp>

#include <rpi-hw/iface/encoder-in.hpp>
#include <rpi-hw/iface/encoder-in-inl.hpp>

#include <rpi-hw/iface/decoder-out.hpp>
#include <rpi-hw/iface/decoder-out-inl.hpp>

#include <rpi-hw/iface/decoder-in.hpp>
#include <rpi-hw/iface/decoder-in-inl.hpp>

#include <rpi-hw/font/glyph.hpp>

#include <rpi-hw/font/base.hpp>

#include <rpi-hw/font/freetype.hpp>
#include <rpi-hw/font/freetype-inl.hpp>

#include <rpi-hw/image/base.hpp>

#include <rpi-hw/image/bitmap.hpp>
#include <rpi-hw/image/bitmap-inl.hpp>

#include <rpi-hw/designer.hpp>
#include <rpi-hw/designer-inl.hpp>

#include <rpi-hw/keypad/base.hpp>
#include <rpi-hw/keypad/base-inl.hpp>

#include <rpi-hw/keypad/matrix.hpp>
#include <rpi-hw/keypad/matrix-inl.hpp>

#include <rpi-hw/display/s7seg.hpp>
#include <rpi-hw/display/s7seg-inl.hpp>

#include <rpi-hw/display/m7seg.hpp>
#include <rpi-hw/display/m7seg-inl.hpp>

#include <rpi-hw/display/hd44780.hpp>
#include <rpi-hw/display/hd44780-inl.hpp>

#include <rpi-hw/display/pcd8544.hpp>
#include <rpi-hw/display/pcd8544-inl.hpp>

#include <rpi-hw/motor/stepper.hpp>
#include <rpi-hw/motor/stepper-inl.hpp>

#endif /* _RPI_HW_HPP_ */
