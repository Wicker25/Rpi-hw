/* 
    Title --- gpio-inl.hpp

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


#ifndef _RPI_HW_GPIO_INL_HPP_
#define _RPI_HW_GPIO_INL_HPP_

namespace rpihw { // Begin main namespace

template < typename T >
void
gpio::expand( uint8_t pin_base, T &expander ) {

	// Check the pin base
	if ( pin_base <= RESERVED_PINS )
		throw exception( utils::format( "(Fatal) `gpio::expand`: pin %d is reserved\n", pin_base ) );

	// Add the I/O expander to the standard GPIO connector
	m_expanders.push_back( { pin_base, static_cast< driver::io_expander * >( &expander ) } );
}

} // End of main namespace

#endif /* _RPI_HW_GPIO_INL_HPP_ */
