/* 
    Title --- iface/shift-in.cpp

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


#ifndef _RPI_HW_IFACE_SHIFT_IN_CPP_
#define _RPI_HW_IFACE_SHIFT_IN_CPP_

#include <rpi-hw/iface/shift-in.hpp>

namespace rpihw { // Begin main namespace

namespace iface { // Begin interfaces namespace

shiftIn::shiftIn( uint8_t data_pin, uint8_t clock_pin, BitOrder order, size_t delay )

	: shiftBase( data_pin, clock_pin, order, delay ) {

	// Initialize the interface pins
	m_gpio->setup( m_pins[ DATA ], INPUT );
	m_gpio->setPullUpDown( m_pins[ DATA ], PULL_DOWN );

	m_gpio->write( m_pins[ CLOCK ], LOW );
	m_gpio->setup( m_pins[ CLOCK ], OUTPUT );
}

shiftIn::~shiftIn() {

}

uint8_t
shiftIn::read() {

	int8_t i;
	uint8_t data = 0;

	if ( m_order == MSBFIRST ) {

		for ( i = 7; i >= 0; --i ) {

			// Read the data to the input pin
			data |= ( (uint8_t) m_gpio->read( m_pins[ DATA ] ) ) << i;

			// Toggle the clock
			strobe();
		}

	} else {

		for ( i = 0; i < 8; ++i ) {

			// Read the data to the input pin
			data |= ( (uint8_t) m_gpio->read( m_pins[ DATA ] ) ) << i;

			// Toggle the clock
			strobe();
		}
	}

	return data;
}

} // End of interfaces namespace

} // End of main namespace

#endif /* _RPI_HW_IFACE_SHIFT_IN_CPP_ */
