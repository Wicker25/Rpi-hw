/* 
    Title --- iface/input.cpp

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


#ifndef _RPI_HW_IFACE_INPUT_CPP_
#define _RPI_HW_IFACE_INPUT_CPP_

#include <rpi-hw/iface/input.hpp>

#include <rpi-hw/utils.hpp>
#include <rpi-hw/utils-inl.hpp>

#include <rpi-hw/mutex.hpp>
#include <rpi-hw/mutex-inl.hpp>

#include <rpi-hw/thread.hpp>
#include <rpi-hw/thread-inl.hpp>

#include <rpi-hw/gpio.hpp>
#include <rpi-hw/gpio-inl.hpp>

#include <rpi-hw/iface/base.hpp>
#include <rpi-hw/iface/base-inl.hpp>

#include <rpi-hw/iface/input-inl.hpp>

namespace rpihw { // Begin main namespace

namespace iface { // Begin interfaces namespace

input::input( uint8_t total, ... ) {

	// Initialize variable argument list
	va_list args;
	va_start( args, total );

	// Initialize the interface
	init( utils::varg< uint8_t, int >( args, total ) );

	// Clean variable argument list
	va_end( args );
}

input::input( const std::vector< uint8_t > &pins ) {

	// Initialize the interface
	init( pins );
}

input::input() {

}

input::~input() {

}

void
input::init( const std::vector< uint8_t > &pins ) {

	// Call parent class method
	base::init( pins );

	// Initialize the interface pins
	size_t i = 0;

	for ( ; i < numOfPins(); i++ ) {

		if ( m_pins[i] != DISABLED_PIN ) {

			m_gpio->setup( m_pins[i], gpio::INPUT );
			m_gpio->setPullUpDown( m_pins[i], gpio::PULL_DOWN );
		}
	}
}

size_t
input::read() const {

	// Read value from the interface
	size_t value = 0, i = 0;

	for ( ; i < numOfPins(); i++ ) {

		if ( m_pins[i] != DISABLED_PIN )
			value |= ( (size_t) m_gpio->read( m_pins[i] ) ) << i;
	}

	return value;
}

bool
input::read( uint8_t pin ) const {

	// Check if pin exists
	if ( pin >= numOfPins() )
		throw exception( "(Error) `iface::read`: could not get pin, index out of range\n" );

	// Return value
	bool value = false;

	// Read value from the interface pin
	if ( m_pins[ pin ] != DISABLED_PIN )
		value = m_gpio->read( m_pins[ pin ] );

	return value;
}

} // End of interfaces namespace

} // End of main namespace

#endif
