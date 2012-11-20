/* 
    Title --- gpio-inl.hpp

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


#ifndef _RPI_HW_GPIO_INL_HPP_
#define _RPI_HW_GPIO_INL_HPP_

namespace rpihw { // Begin main namespace

inline void
gpio::setBit( uint8_t offset, uint8_t index, bool value ) {

	// Calculate the bit position
	uint8_t shift = index % 32;

	// Get GPIO controller register
	uint32_t &reg = *( m_map + offset + index / 32 );

	// Set the bit value on the GPIO controller register
	reg = ( reg & ~( 1 << shift ) ) | ( value << shift );
}

inline bool
gpio::getBit( uint8_t offset, uint8_t index ) const {

	// Return the bit value from one of the GPIO controller registers
	return ( *( m_map + offset + index / 32 ) & ( 1 << ( index % 32 ) ) ) != 0;
}

inline void
gpio::waitCycles( size_t cycles ) const {

	// Wait some cycles
    while ( cycles-- ) asm volatile( "nop" );
}

inline void
gpio::write( uint8_t pin, bool value ) {

	// Set the value of the output pin
	// 0 = Low
	// 1 = High
	*( m_map + ( value ? GPSET0 : GPCLR0 ) + ( pin / 32 ) ) = 1 << ( pin % 32 );
}

inline bool
gpio::read( uint8_t pin ) const {

	// Return the value of the input pin
	// 0 = Low
	// 1 = High
	return getBit( GPLEV0, pin );
}

inline bool
gpio::checkEvent( uint8_t pin ) const {

	// Return event state of the GPIO pin
	// 0 = Event not detected on the GPIO pin
	// 1 = Event detected on the GPIO pin
	return getBit( GPEDS0, pin );
}

inline void
gpio::setRisingEvent( uint8_t pin, bool enabled ) {

	// Enable/disable rising edge event on the GPIO pin
	// 0 = Disabled
	// 1 = Enabled
	setBit( GPREN0, pin, enabled );
}

inline void
gpio::setFallingEvent( uint8_t pin, bool enabled ) {

	// Enable/disable falling edge event on the GPIO pin
	// 0 = Disabled
	// 1 = Enabled
	setBit( GPFEN0, pin, enabled );
}

inline void
gpio::setHighEvent( uint8_t pin, bool enabled ) {

	// Enable/disable high event on the GPIO pin
	// 0 = Disabled
	// 1 = Enabled
	setBit( GPHEN0, pin, enabled );
}

inline void
gpio::setLowEvent( uint8_t pin, bool enabled ) {

	// Enable/disable low event on the GPIO pin
	// 0 = Disabled
	// 1 = Enabled
	setBit( GPLEN0, pin, enabled );
}

} // End of main namespace

#endif
