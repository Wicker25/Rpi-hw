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
