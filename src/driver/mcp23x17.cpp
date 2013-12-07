/* 
    Title --- driver/mcp23x17.cpp

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


#ifndef _RPI_HW_DRIVER_MCP23X17_CPP_
#define _RPI_HW_DRIVER_MCP23X17_CPP_

#include <rpi-hw/driver/mcp23x17.hpp>

namespace rpihw { // Begin main namespace

namespace driver { // Begin drivers namespace

mcp23x17::mcp23x17( const std::string &dev_path ) : m_dev_path( dev_path ) {

	// Set the GPIOs modes
	m_states[0] = 0xFF;
	m_states[1] = 0xFF;

	// Set the GPIOs pullup controls
	m_states[4] = 0x00;
	m_states[5] = 0x00;
}

mcp23x17::~mcp23x17() {

}

void
mcp23x17::init() {

	// Initialize the device
	send( IOCON, SEQOP | HAEN );
	send( IOCON + 1, SEQOP | HAEN );

	// Set the GPIOs states
	m_states[2] = receive( OLAT );
	m_states[3] = receive( OLAT + 1 );
}

void
mcp23x17::setup( uint8_t pin, uint8_t mode, uint8_t pull_mode ) {

	// Enable/disable pull-up control on the GPIO pin
	if ( mode == INPUT )
		setPullUpDown( pin, pull_mode );

	uint8_t reg = pin / 8;

	// Update the local register
	utils::set_bit( m_states, reg, pin % 8, mode ? 0 : 1 );

	// Set the mode of the GPIO pin
	send( IODIR + reg, m_states[ reg ] );
}

void
mcp23x17::write( uint8_t pin, bool value ) {

	uint8_t reg = pin / 8, off = reg + 2;

	// Update the local register
	utils::set_bit( m_states, off, pin % 8, value );

	// Set the value of the output pin
	send( GPIO + reg, m_states[ off ] );
}

bool
mcp23x17::read( uint8_t pin ) {

	uint8_t reg = pin / 8, off = reg + 4;

	// Update the local register
	m_states[ off ] = receive( GPIO + reg );

	// Return the value of the input pin
	return utils::get_bit( m_states, off, pin % 8 );
}

void
mcp23x17::setPullUpDown( uint8_t pin, uint8_t mode ) {

	uint8_t reg = pin / 8, off = reg + 4;

	// Update the local register
	utils::set_bit( m_states, off, pin % 8, mode );

	// Enable/disable the pull-up control on a GPIO pin
	send( GPPU + reg, m_states[ off ] );
}

} // End of drivers namespace

} // End of main namespace

#endif /* _RPI_HW_DRIVER_MCP23X17_CPP_ */
