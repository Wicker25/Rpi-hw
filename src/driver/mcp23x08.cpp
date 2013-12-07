/* 
    Title --- driver/mcp23x08.cpp

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


#ifndef _RPI_HW_DRIVER_MCP23X08_CPP_
#define _RPI_HW_DRIVER_MCP23X08_CPP_

#include <rpi-hw/driver/mcp23x08.hpp>

namespace rpihw { // Begin main namespace

namespace driver { // Begin drivers namespace

mcp23x08::mcp23x08( const std::string &dev_path ) : m_dev_path( dev_path ) {

	// Set the GPIOs modes
	m_states[0] = 0xFF;

	// Set the GPIOs pullup controls
	m_states[3] = 0x00;
}

mcp23x08::~mcp23x08() {

}

void
mcp23x08::init() {

	// Initialize the device
	send( IOCON, SEQOP | HAEN );

	// Set the GPIOs states
	m_states[1] = receive( OLAT );
	m_states[2] = 0x00;
}

void
mcp23x08::setup( uint8_t pin, uint8_t mode, uint8_t pull_mode ) {

	// Enable/disable pull-up control on the GPIO pin
	if ( mode == INPUT )
		setPullUpDown( pin, pull_mode );

	// Update the local register
	utils::set_bit( m_states, 0, pin, mode ? 0 : 1 );

	// Set the mode of the GPIO pin
	send( IODIR, m_states[0] );
}

void
mcp23x08::write( uint8_t pin, bool value ) {

	// Update the local register
	utils::set_bit( m_states, 1, pin, value );

	// Set the value of the output pin
	send( GPIO, m_states[1] );
}

bool
mcp23x08::read( uint8_t pin ) {

	// Update the local register
	m_states[2] = receive( GPIO );

	// Return the value of the input pin
	return utils::get_bit( m_states, 2, pin );
}

void
mcp23x08::setPullUpDown( uint8_t pin, uint8_t mode ) {

	// Update the local register
	utils::set_bit( m_states, 3, pin, (bool) mode );

	// Enable/disable the pull-up control on a GPIO pin
	send( GPPU, m_states[3] );
}

} // End of drivers namespace

} // End of main namespace

#endif /* _RPI_HW_DRIVER_MCP23X08_CPP_ */
