/* 
    Title --- iface/output.cpp

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


#ifndef _RPI_HW_IFACE_OUTPUT_CPP_
#define _RPI_HW_IFACE_OUTPUT_CPP_

#include <rpi-hw/iface/output.hpp>

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

#include <rpi-hw/iface/output-inl.hpp>

namespace rpihw { // Begin main namespace

namespace iface { // Begin interfaces namespace

output::output( uint8_t total, ... ) {

	// Initialize variable argument list
	va_list args;
	va_start( args, total );

	// Initialize the interface
	init( utils::varg< uint8_t, int >( args, total ) );

	// Clean variable argument list
	va_end( args );
}

output::output( const std::vector< uint8_t > &pins ) {

	// Initialize the interface
	init( pins );
}

output::output() {

}

output::~output() {

}

void
output::init( const std::vector< uint8_t > &pins ) {

	// Call parent class method
	base::init( pins );

	// Initialize the interface pins
	size_t i = 0;

	for ( ; i < numOfPins(); i++ ) {

		if ( m_pins[i] != DISABLED_PIN ) {

			m_gpio->write( m_pins[i], gpio::LOW );
			m_gpio->setup( m_pins[i], gpio::OUTPUT );
		}
	}
}

void
output::write( size_t value ) {

	// Write value on the interface
	size_t i = 0;

	for ( ; i < numOfPins(); i++ ) {

		if ( m_pins[i] != DISABLED_PIN )
			m_gpio->write( m_pins[i], value & ( 1 << i ) );
	}
}

void
output::write( uint8_t pin, bool value ) {

	// Check if pin exists
	if ( pin >= numOfPins() )
		throw exception( "(Error) `iface::write`: could not get pin, index out of range\n" );

	// Write value on the interface pin
	if ( m_pins[ pin ] != DISABLED_PIN )
		m_gpio->write( m_pins[ pin ], value );
}

} // End of interfaces namespace

} // End of main namespace

#endif
