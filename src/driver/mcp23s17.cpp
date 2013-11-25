/* 
    Title --- driver/mcp23s17.cpp

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


#ifndef _RPI_HW_DRIVER_MCP23S17_CPP_
#define _RPI_HW_DRIVER_MCP23S17_CPP_

#include <rpi-hw/driver/mcp23s17.hpp>

namespace rpihw { // Begin main namespace

namespace driver { // Begin drivers namespace

mcp23s17::mcp23s17( const std::string &dev_path, uint8_t device_id )

	: m_spi			( new driver::spi( dev_path, driver::spi::MODE_0, 8, 10000000 ) )
	, m_device_id	( device_id ) {

	// Initialize the device
	send( IOCON, SEQOP | HAEN );
	send( IOCON + 1, SEQOP | HAEN );

	// Set the GPIOs modes
	m_states[0] = 0xFF;
	m_states[1] = 0xFF;

	// Set the GPIOs states
	m_states[2] = receive( OLAT );
	m_states[3] = receive( OLAT + 1 );

	// Set the GPIOs pullup controls
	m_states[4] = 0x00;
	m_states[5] = 0x00;
}

mcp23s17::~mcp23s17() {

	// Destroy the SPI controller
	delete m_spi;
}

void
mcp23s17::setup( uint8_t pin, uint8_t mode, uint8_t pud_mode ) {

	// Enable/disable pull-up control on the GPIO pin
	if ( mode == INPUT )
		setPullUpDown( pin, pud_mode );

	uint8_t offset = pin / 8;

	utils::set_bit( m_states, offset, pin % 8, mode ? 0 : 1 );

	// Set the mode of the GPIO pin
	send( IODIR + pin / 8, m_states[ offset ] );
}

void
mcp23s17::write( uint8_t pin, bool value ) {

	uint8_t offset = pin / 8 + 2;

	utils::set_bit( m_states, offset, pin % 8, value );

	// Set the value of the output pin
	send( GPIO + pin / 8, m_states[ offset ] );
}

bool
mcp23s17::read( uint8_t pin ) {

	uint8_t offset = pin / 8 + 2;

	m_states[ offset ] = receive( GPIO + pin / 8 );

	// Return the value of the input pin
	return utils::get_bit( m_states, offset, pin % 8 );
}

void
mcp23s17::setPullUpDown( uint8_t pin, uint8_t mode ) {

	uint8_t offset = pin / 8 + 4;

	utils::set_bit( m_states, offset, pin % 8, mode );

	// Enable/disable the pull-up control on a GPIO pin
	send( GPPU + pin / 8, m_states[ offset ] );
}

} // End of drivers namespace

} // End of main namespace

#endif /* _RPI_HW_DRIVER_MCP23S17_CPP_ */
