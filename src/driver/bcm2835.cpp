/* 
    Title --- driver/bcm2835.cpp

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


#ifndef _RPI_HW_IFACE_BCM2835_CPP_
#define _RPI_HW_IFACE_BCM2835_CPP_

#include <rpi-hw/driver/bcm2835.hpp>

namespace rpihw { // Begin main namespace

namespace driver { // Begin drivers namespace

bcm2835::bcm2835() {

	// Open memory device file
	m_mem_fd = open( "/dev/mem", O_RDWR | O_SYNC );

	if ( m_mem_fd < 0 )
		throw exception( "(Fatal) `gpio`: can't open `/dev/mem`, you must be 'root' to run this software!" );


	// Map the GPIO controller memory
	m_gpio = (volatile uint32_t *) mmap(

		0,
		BLOCK_SIZE,
		PROT_READ | PROT_WRITE,
		MAP_SHARED,
		m_mem_fd,
		GPIO_BASE
	);

	// Handle possible errors
	if ( m_gpio == MAP_FAILED )
		throw exception( utils::format( "(Fatal) `gpio`: mapping error at address %p (gpio)\n", m_gpio ) );


	// Map the PWM controller memory
	m_pwm = (volatile uint32_t *) mmap(

		0,
		BLOCK_SIZE,
		PROT_READ | PROT_WRITE,
		MAP_SHARED,
		m_mem_fd,
		GPIO_PWM
	);

	// Handle possible errors
	if ( m_pwm == MAP_FAILED )
		throw exception( utils::format( "(Fatal) `gpio`: mapping error at address %p (pwm)\n", m_pwm ) );
}

bcm2835::~bcm2835() {

	// Unmap GPIO controller memory
	munmap( (uint32_t *) m_gpio, BLOCK_SIZE );

	// Unmap PWM controller memory
	munmap( (uint32_t *) m_pwm, BLOCK_SIZE );

	// Close memory device file
	close( m_mem_fd );
}

void
bcm2835::setup( uint8_t pin, uint8_t mode, uint8_t pull_mode ) {

	// Enable/disable pull-up/down control on the GPIO pin
	if ( mode == INPUT )
		setPullUpDown( pin, pull_mode );

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
bcm2835::setPullUpDown( uint8_t pin, uint8_t mode ) {

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

} // End of drivers namespace

} // End of main namespace

#endif /* _RPI_HW_IFACE_BCM2835_CPP_ */
