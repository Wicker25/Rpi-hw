/* 
    Title --- driver/bcm2835-inl.hpp

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


#ifndef _RPI_HW_IFACE_BCM2835_INL_HPP_
#define _RPI_HW_IFACE_BCM2835_INL_HPP_

namespace rpihw { // Begin main namespace

namespace driver { // Begin drivers namespace

inline void
bcm2835::setBit( uint8_t offset, uint8_t index, bool value ) {

	// Set the bit value on the GPIO controller register
	utils::set_bit( m_gpio, offset + index / 32, index % 32, value );
}

inline bool
bcm2835::getBit( uint8_t offset, uint8_t index ) const {

	// Return the bit value from one of the GPIO controller registers
	return utils::get_bit( m_gpio, offset + index / 32, index % 32 );
}

inline void
bcm2835::waitCycles( size_t cycles ) const {

	// Wait some CPU cycles
    while ( --cycles ) asm volatile( "nop" );
}

inline void
bcm2835::write( uint8_t pin, bool value ) {

	// Set the value of the output pin
	// 0 = Low
	// 1 = High
	*( m_gpio + ( value ? GPSET0 : GPCLR0 ) + pin / 32 ) = 1 << ( pin % 32 );
}

inline bool
bcm2835::read( uint8_t pin ) const {

	// Return the value of the input pin
	// 0 = Low
	// 1 = High
	return getBit( GPLEV0, pin );
}

inline bool
bcm2835::checkEvent( uint8_t pin ) const {

	// Return event state of the GPIO pin
	// 0 = Event not detected on the GPIO pin
	// 1 = Event detected on the GPIO pin
	return getBit( GPEDS0, pin );
}

inline void
bcm2835::setRisingEvent( uint8_t pin, bool enabled ) {

	// Enable/disable rising edge event on the GPIO pin
	// 0 = Disabled
	// 1 = Enabled
	setBit( GPREN0, pin, enabled );
}

inline void
bcm2835::setFallingEvent( uint8_t pin, bool enabled ) {

	// Enable/disable falling edge event on the GPIO pin
	// 0 = Disabled
	// 1 = Enabled
	setBit( GPFEN0, pin, enabled );
}

inline void
bcm2835::setHighEvent( uint8_t pin, bool enabled ) {

	// Enable/disable high event on the GPIO pin
	// 0 = Disabled
	// 1 = Enabled
	setBit( GPHEN0, pin, enabled );
}

inline void
bcm2835::setLowEvent( uint8_t pin, bool enabled ) {

	// Enable/disable low event on the GPIO pin
	// 0 = Disabled
	// 1 = Enabled
	setBit( GPLEN0, pin, enabled );
}

} // End of drivers namespace

} // End of main namespace

#endif /* _RPI_HW_IFACE_BCM2835_INL_HPP_ */
