/* 
    Title --- iface/shift-base.cpp

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


#ifndef _RPI_HW_IFACE_SHIFT_BASE_CPP_
#define _RPI_HW_IFACE_SHIFT_BASE_CPP_

#include <rpi-hw/iface/shift-base.hpp>

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

#include <rpi-hw/iface/base.hpp>
#include <rpi-hw/iface/base-inl.hpp>

#include <rpi-hw/iface/shift-base-inl.hpp>

namespace rpihw { // Begin main namespace

namespace iface { // Begin interfaces namespace

shiftBase::shiftBase( uint8_t data_pin, uint8_t clock_pin, BitOrder order, size_t delay ) : base( 2, data_pin, clock_pin ) {

	// Store the bit order and the delay time of the clock
	m_order = order;
	m_delay = delay;
}

shiftBase::~shiftBase() {

}

} // End of interfaces namespace

} // End of main namespace

#endif
