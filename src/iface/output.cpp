/* 
    Title --- iface/output.cpp

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


#ifndef _RPI_HW_IFACE_OUTPUT_CPP_
#define _RPI_HW_IFACE_OUTPUT_CPP_

#include <rpi-hw/iface/output.hpp>

namespace rpihw { // Begin main namespace

namespace iface { // Begin interfaces namespace

output::output( std::initializer_list< uint8_t > pins ) : iface::base( pins ) {

	// Initialize the interface pins
	for ( auto &pin : m_pins ) {

		m_gpio->write( pin, gpio::LOW );
		m_gpio->setup( pin, gpio::OUTPUT );
	}
}

output::output( const std::vector< uint8_t > &pins ) : iface::base( pins ) {

	// Initialize the interface pins
	for ( auto &pin : m_pins ) {

		m_gpio->write( pin, gpio::LOW );
		m_gpio->setup( pin, gpio::OUTPUT );
	}
}

output::~output() {

}

void
output::write( size_t data ) {

	// Write data on the interface
	size_t i = 0;

	for ( ; i < numOfPins(); ++i )
		m_gpio->write( m_pins[i], data & ( 1 << i ) );
}

void
output::write( uint8_t index, bool data ) {

	// Check if pin exists
	if ( index >= numOfPins() )
		throw exception( "(Error) `iface::write`: could not get pin, index out of range\n" );

	// Write data on the interface pin
	m_gpio->write( m_pins[ index ], data );
}

} // End of interfaces namespace

} // End of main namespace

#endif /* _RPI_HW_IFACE_OUTPUT_CPP_ */
