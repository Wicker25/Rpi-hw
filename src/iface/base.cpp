/* 
    Title --- iface/base.cpp

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


#ifndef _RPI_HW_BASE_CPP_
#define _RPI_HW_BASE_CPP_

#include <rpi-hw/iface/base.hpp>

#include <rpi-hw/utils.hpp>
#include <rpi-hw/utils-inl.hpp>

#include <rpi-hw/mutex.hpp>
#include <rpi-hw/mutex-inl.hpp>

#include <rpi-hw/thread.hpp>
#include <rpi-hw/thread-inl.hpp>

#include <rpi-hw/gpio.hpp>
#include <rpi-hw/gpio-inl.hpp>

#include <rpi-hw/iface/base-inl.hpp>

namespace rpihw { // Begin main namespace

namespace iface { // Begin interfaces namespace

base::base() {

	// Create the GPIO controller interface
	m_gpio = new gpio;
}

base::base( uint8_t total, ... ) {

	// Create the GPIO controller interface
	m_gpio = new gpio;

	// Initialize variable argument list
	va_list args;
	va_start( args, total );

	// Initialize the interface
	init( utils::varg< uint8_t, int >( args, total ) );

	// Clean variable argument list
	va_end( args );
}

base::base( const std::vector< uint8_t > &pins ) {

	// Create the GPIO controller interface
	m_gpio = new gpio;

	// Initialize the interface
	init( pins );
}

base::~base() {

	// Destroy the vector containing interface pins
	delete[] m_pins;

	// Destroy the GPIO controller interface
	delete m_gpio;
}

void
base::init( const std::vector< uint8_t > &pins ) {

	// Create vector containing the interface pins
	m_total = (uint8_t) pins.size();
	m_pins = utils::malloc< uint8_t >( pins );
}

void
base::setPin( uint8_t index, uint8_t pin ) {

	// Check if the interface pin exists
	if ( index >= m_total )
		throw exception( "(Error) `iface::setPin`: wrong pin index\n" );

	// Store the interface pin
	m_pins[ index ] = pin;
}

} // End of interfaces namespace

} // End of main namespace

#endif
