/* 
    Title --- iface/base.hpp

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


#ifndef _RPI_HW_BASE_HPP_
#define _RPI_HW_BASE_HPP_

#include <vector>

#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>
#include <rpi-hw/utils.hpp>

#include <rpi-hw/gpio.hpp>

namespace rpihw { // Begin main namespace

namespace iface { // Begin interfaces namespace

// Disabled pin id
const uint8_t DISABLED_PIN = 255;

/* GENERIC INTERFACE */
class base {

public:

	// Constructor and destructor methods
	base( uint8_t total, ... );
	base( const std::vector< uint8_t > &pins );
	virtual ~base();

	// Sets a interface pin
	virtual void setPin( uint8_t index, uint8_t pin );
	// Returns a interface pin
	virtual uint8_t getPin( uint8_t index ) const;

	// Returns the number of pins
	virtual uint8_t numOfPins() const;

protected:

	// GPIO controller interface
	gpio *m_gpio;

	// Number of pins
	uint8_t m_total;

	// Vector containing interface pins
	uint8_t *m_pins;

	// Constructor method (only for child class)
	base();

	// Initializes the interface
	virtual void init( const std::vector< uint8_t > &pins );
};

} // End of interfaces namespace

} // End of main namespace

#endif
