/* 
    Title --- iface/gpio.cpp

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


#ifndef _RPI_HW_IFACE_GPIO_CPP_
#define _RPI_HW_IFACE_GPIO_CPP_

#include <rpi-hw/iface/gpio.hpp>

namespace rpihw { // Begin main namespace

namespace iface { // Begin interfaces namespace

gpio::gpio() {

	// Map the GPIO controller memory
	static devmap gpio_map( "/dev/mem", BLOCK_SIZE, GPIO_BASE );
	m_gpio = gpio_map.data();

	// Map the PWM controller memory
	static devmap pwm_map( "/dev/mem", BLOCK_SIZE, GPIO_PWM );
	m_pwm = pwm_map.data();
}

gpio::~gpio() {

}

void
gpio::setup( uint8_t pin, PinMode mode, PullMode pud_mode ) {

	// Enable/disable pull-up/down control on the GPIO pin
	if ( mode == INPUT ) setPullUpDown( pin, pud_mode );

	// Calculate the bit position
	uint8_t shift = ( pin % 10 ) * 3;

	// Get GPIO controller register
	volatile uint32_t &reg = *( m_gpio + GPFSEL0 + ( pin / 10 ) );

	// Sets the GPIO pin mode
	// 000 = Input
	// 001 = Output
	reg = ( reg & ~( 7 << shift ) ) | ( (uint32_t) mode << shift );
}

void
gpio::setPullUpDown( uint8_t pin, PullMode mode ) {

	// Get the GPIO controller registers
	volatile uint32_t	&reg_pullupdown	= *( m_gpio + GPPUD0 ),
						&reg_clock		= *( m_gpio + GPPUDCLK0 + ( pin / 32 ) );

	// Enable/disable pull-up/down control on the GPIO pin
	// 00 = Disable pull-up/down
	// 01 = Enable pull-down control
	// 10 = Enable pull-up control
	// 11 = Reserved
	reg_pullupdown = (uint32_t) mode;

	// Set clock con pin
    waitCycles( 150 );
	reg_clock = 1 << ( pin % 32 );
    waitCycles( 150 );

	// Restore the registers
	reg_clock = 0;
	reg_pullupdown = 0;
}

} // End of interfaces namespace

} // End of main namespace

#endif /* _RPI_HW_IFACE_GPIO_CPP_ */
