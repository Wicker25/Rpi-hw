/* 
    Title --- gpio.cpp

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


#ifndef _RPI_HW_GPIO_CPP_
#define _RPI_HW_GPIO_CPP_

#include <rpi-hw/gpio.hpp>

namespace rpihw { // Begin main namespace

gpio &
gpio::get() {

	// Return the singleton instance
	static gpio instance;
	return instance;
}

gpio::gpio() : m_bcm2835( new driver::bcm2835 ) {

}

gpio::~gpio() {

	// Destroy the BCM2835 controller
	delete m_bcm2835;
}

driver::ioexpander *
gpio::findExpander( uint8_t &pin ) {

	// Find the I/O expander with the specific pin index
	for ( auto it = m_expanders.rbegin(); it != m_expanders.rend(); ++it ) {

		if ( pin >= it->pin_base ) {

			pin -= it->pin_base;
			return it->expander;
		}
	}

	// Else throw an exception
	throw exception( utils::format( "(Fatal) `ioexpander::findExpander`: there's not I/O expander for pin %u", pin ) );

	return nullptr;
}

void
gpio::setup( uint8_t pin, uint8_t mode, uint8_t pud_mode ) {

	// Set the mode of a GPIO pin
	if ( pin <= RESERVED_PINS )
		m_bcm2835->setup( pin, mode, pud_mode );

	else {

		driver::ioexpander *expander = findExpander( pin );
		expander->setup( pin, mode, pud_mode );
	}
}

void
gpio::write( uint8_t pin, bool value ) {

	// Set the value of a output pin
	if ( pin <= RESERVED_PINS )
		m_bcm2835->write( pin, value );

	else {

		driver::ioexpander *expander = findExpander( pin );
		expander->write( pin, value );
	}
}

bool
gpio::read( uint8_t pin ) {

	// Return the value of a input pin
	if ( pin <= RESERVED_PINS )
		return m_bcm2835->read( pin );

	driver::ioexpander *expander = findExpander( pin );
	return expander->read( pin );
}

bool
gpio::checkEvent( uint8_t pin ) {

	// Return the event state of a GPIO pin
	if ( pin <= RESERVED_PINS )
		return m_bcm2835->checkEvent( pin );

	driver::ioexpander *expander = findExpander( pin );
	return expander->checkEvent( pin );
}

void
gpio::setRisingEvent( uint8_t pin, bool enabled ) {

	// Enable/disable the rising edge event on a GPIO pin
	if ( pin <= RESERVED_PINS )
		m_bcm2835->setRisingEvent( pin, enabled );

	else {

		driver::ioexpander *expander = findExpander( pin );
		expander->setRisingEvent( pin, enabled );
	}
}

void
gpio::setFallingEvent( uint8_t pin, bool enabled ) {

	// Enable/disable the falling edge event on a GPIO pin
	if ( pin <= RESERVED_PINS )
		m_bcm2835->setFallingEvent( pin, enabled );

	else {

		driver::ioexpander *expander = findExpander( pin );
		expander->setFallingEvent( pin, enabled );
	}
}

void
gpio::setHighEvent( uint8_t pin, bool enabled ) {

	// Enable/disable the high event on a GPIO pin
	if ( pin <= RESERVED_PINS )
		m_bcm2835->setHighEvent( pin, enabled );

	else {

		driver::ioexpander *expander = findExpander( pin );
		expander->setHighEvent( pin, enabled );
	}
}

void
gpio::setLowEvent( uint8_t pin, bool enabled ) {

	// Enable/disable the low event on a GPIO pin
	if ( pin <= RESERVED_PINS )
		m_bcm2835->setLowEvent( pin, enabled );

	else {

		driver::ioexpander *expander = findExpander( pin );
		expander->setLowEvent( pin, enabled );
	}
}

void
gpio::setPullUpDown( uint8_t pin, uint8_t mode ) {

	// Enable/disable the pull-up/down control on a GPIO pin
	if ( pin <= RESERVED_PINS )
		m_bcm2835->setPullUpDown( pin, mode );

	else {

		driver::ioexpander *expander = findExpander( pin );
		expander->setPullUpDown( pin, mode );
	}
}

} // End of main namespace

#endif /* _RPI_HW_GPIO_CPP_ */
