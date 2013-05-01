/* 
    Title --- iface/shift-out.cpp

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


#ifndef _RPI_HW_IFACE_SHIFT_OUT_CPP_
#define _RPI_HW_IFACE_SHIFT_OUT_CPP_

#include <rpi-hw/iface/shift-out.hpp>

namespace rpihw { // Begin main namespace

namespace iface { // Begin interfaces namespace

shiftOut::shiftOut( uint8_t data_pin, uint8_t clock_pin, BitOrder order, size_t delay ) : shiftBase( data_pin, clock_pin, order, delay ) {

	// Initialize the interface pins
	m_gpio->write( m_pins[ DATA_PIN ], gpio::LOW );
	m_gpio->setup( m_pins[ DATA_PIN ], gpio::OUTPUT );

	m_gpio->write( m_pins[ CLOCK_PIN ], gpio::LOW );
	m_gpio->setup( m_pins[ CLOCK_PIN ], gpio::OUTPUT );
}

shiftOut::~shiftOut() {

}

void
shiftOut::write( uint8_t data ) {

	int8_t i;

	if ( m_order == MSBFIRST ) {

		for ( i = 7; i >= 0; --i ) {

			// Write the data to the output pin
			m_gpio->write( m_pins[ DATA_PIN ], data & ( 1 << i ) );

			// Toggle the clock
			strobe();
		}

	} else {

		for ( i = 0; i < 8; ++i ) {

			// Write the data to the output pin
			m_gpio->write( m_pins[ DATA_PIN ], data & ( 1 << i ) );

			// Toggle the clock
			strobe();
		}
	}
}

} // End of interfaces namespace

} // End of main namespace

#endif /* _RPI_HW_IFACE_SHIFT_OUT_CPP_ */
