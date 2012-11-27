/* 
    Title --- rpi-hw.hpp [main]

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


#ifndef _RPI_HW_HPP_
#define _RPI_HW_HPP_

/*!
	@mainpage Rpi-hw v0.2.3 - Reference Manual

	@section description Description

	<a style="font-weight: bold;" href="http://www.hackyourmind.org/blog/projects/rpi-hw/" target="_blank">Rpi-hw</a> is a free C++ library designed to manage the Raspberry Pi's General Purpose Input/Output (GPIO) connector.\n
	The library is released under terms of the <a href="http://en.wikipedia.org/wiki/GNU_Lesser_General_Public_License" target="_blank">GNU LGPL v3</a>.

	The source of the latest version of Rpi-hw is available on <a href="https://github.com/Wicker25/Rpi-hw" target="_blank">github.com</a> at:

	@li <a href="https://github.com/Wicker25/Rpi-hw" target="_blank">https://github.com/Wicker25/Rpi-hw</a>

	@section main_functions Main functions

	The following are some functions of the library:

	@li Low-level management of the GPIOs
	@li Generic input/output by interfaces
	@li Keypad support (matrix keypad)
	@li Display support (7-segments, HD44780 lcd)

	@section compiling_and_install Compiling and install the library

	First of all, you need to clone the Rpi-hw repository:
	@verbatim $ git clone https://github.com/Wicker25/Rpi-hw @endverbatim

	Then, compile and install the library with:
	@verbatim
$ cd Rpi-hw
$ cmake ./ -DCMAKE_INSTALL_PREFIX=<PATH>
$ make
# make install @endverbatim

	Also, if you want a local copy of the documentation, you can generate it using <a href="https://en.wikipedia.org/wiki/Doxygen" target="_blank">doxygen</a>:

    @verbatim $ make doc @endverbatim

	@section using_the_library Using the library

	To use the library, you must include the main Rpi-hw‘s header file into your program:

	@code
// Include the main header file
#include <rpi-hw.hpp>
	@endcode

	Then, you link the program's file with the library object file, adding a command line argument to the compiler:
	@verbatim $ g++ `pkg-config --libs --cflags rpi-hw` <SOURCE> -o <BIN> @endverbatim

	Otherwise, you can use <a href="http://en.wikipedia.org/wiki/CMake" target="_blank">CMake</a> with the module \a FindRpiHw.cmake provided by the library. See the following example:

	@verbatim
# CMake's configuration

# Set the minimum required version of cmake for this project
cmake_minimum_required( VERSION 2.6 )

# Find Rpi-hw library on the operating system
find_package( RpiHw )

# Check if the library was found
IF ( RPI_HW_FOUND )

        # Compile the project
        add_executable( <BIN> ${CMAKE_SOURCE_DIR}/<SOURCE> )

        # Link the library
        target_link_libraries( <BIN> ${RPI_HW_LIBRARIES} )

ENDIF ( RPI_HW_FOUND ) @endverbatim

	@section examples Examples

	If you are looking for examples, you can find some in the section <a href="examples.html">examples</a> or on my <a href="http://www.hackyourmind.org/blog/" target="_blank">blog</a>.

	@section links Links

	@li <a href="http://www.hackyourmind.org/blog/" target="_blank">http://www.hackyourmind.org/blog/</a>
*/

/*!
	@namespace rpihw
	@brief Main namespace of the library.
*/

// Includes all Rpi-hw header files
#include <rpi-hw/version.hpp>
#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>
#include <rpi-hw/math.hpp>

#include <rpi-hw/utils.hpp>
#include <rpi-hw/utils-inl.hpp>

#include <rpi-hw/bitset.hpp>
#include <rpi-hw/bitset-inl.hpp>

#include <rpi-hw/mutex.hpp>
#include <rpi-hw/mutex-inl.hpp>

#include <rpi-hw/thread.hpp>
#include <rpi-hw/thread-inl.hpp>

#include <rpi-hw/rpi.hpp>

#include <rpi-hw/gpio.hpp>
#include <rpi-hw/gpio-inl.hpp>

#include <rpi-hw/iface/base.hpp>
#include <rpi-hw/iface/base-inl.hpp>

#include <rpi-hw/iface/output.hpp>
#include <rpi-hw/iface/output-inl.hpp>

#include <rpi-hw/iface/input.hpp>
#include <rpi-hw/iface/input-inl.hpp>

#include <rpi-hw/iface/decoder.hpp>
#include <rpi-hw/iface/decoder-inl.hpp>

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

#endif
