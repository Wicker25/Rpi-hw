/* 
    Title --- iface/input.cpp

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


#ifndef _RPI_HW_IFACE_INPUT_CPP_
#define _RPI_HW_IFACE_INPUT_CPP_

#include <rpi-hw/iface/input.hpp>

namespace rpihw { // Begin main namespace

namespace iface { // Begin interfaces namespace

input::input( std::initializer_list< uint8_t > pins, uint8_t pull_mode ) : iface::base( pins ), m_pull_mode( pull_mode ) {

	// Initialize the interface pins
	for ( auto &pin : m_pins )
		m_gpio->setup( pin, INPUT, m_pull_mode );
}

input::input( const std::vector< uint8_t > &pins, uint8_t pull_mode ) : iface::base( pins ), m_pull_mode( pull_mode ) {

	// Initialize the interface pins
	for ( auto &pin : m_pins )
		m_gpio->setup( pin, INPUT, m_pull_mode );
}

input::~input() {

}

size_t
input::read() const {

	// Read data from the interface
	size_t data = 0, i = 0;

	for ( ; i < size(); ++i )
		data |= ( (size_t) m_gpio->read( m_pins[i] ) ) << i;

	return data;
}

bool
input::read( uint8_t index ) const {

	// Check if pin exists
	if ( index >= size() )
		throw exception( "(Fatal) `iface::read`: could not get pin, index out of range\n" );

	// Return data
	bool data = 0;

	// Read data from the interface pin
	data = m_gpio->read( m_pins[ index ] );

	return data;
}

} // End of interfaces namespace

} // End of main namespace

#endif /* _RPI_HW_IFACE_INPUT_CPP_ */
