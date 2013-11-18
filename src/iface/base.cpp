/* 
    Title --- iface/base.cpp

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


#ifndef _RPI_HW_IFACE_BASE_CPP_
#define _RPI_HW_IFACE_BASE_CPP_

#include <rpi-hw/iface/base.hpp>

namespace rpihw { // Begin main namespace

namespace iface { // Begin interfaces namespace

base::base( std::initializer_list< uint8_t > pins ) : m_pins( pins ), m_gpio( &m_gpio->get() ) {

}

base::base( const std::vector< uint8_t > &pins ) : m_pins( pins ) {

}

base::~base() {

}

void
base::setPin( uint8_t index, uint8_t pin ) {

	// Check if the interface pin exists
	if ( index >= m_pins.size() )
		throw exception( "(Fatal) `iface::setPin`: wrong pin index\n" );

	// Store the interface pin
	m_pins[ index ] = pin;
}

} // End of interfaces namespace

} // End of main namespace

#endif /* _RPI_HW_IFACE_BASE_CPP_ */
