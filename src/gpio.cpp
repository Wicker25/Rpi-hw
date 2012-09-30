/* 
    Title --- gpio.cpp

    Copyright (C) 2010 Giacomo Trudu - wicker25[at]gmail[dot]com

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


#ifndef _RPI_HW_GPIO_CPP_
#define _RPI_HW_GPIO_CPP_

#include <rpi-hw/gpio.hpp>
#include <rpi-hw/gpio-inl.hpp>

namespace rpihw { // Namespace di Rpi-hw

gpio::gpio() {

	// Apro il dispositivo `/dev/mem`
	this->mem_fd = open( "/dev/mem", O_RDWR | O_SYNC );

	if ( this->mem_fd < 0 ) {

		throw exception( "Can't open /dev/mem : you must be 'root' to run this software!" );
	}

	// Effettuo il mapping dell'area di memoria relativa al controller gpio
	this->map = (uint32_t *) mmap(

		0,
		BLOCK_SIZE,
		PROT_READ | PROT_WRITE,
		MAP_SHARED,
		mem_fd,
		GPIO_BASE
	);

	// Gestisco eventuali errori
	if ( this->map == MAP_FAILED ) {

		throw exception( macro::format( "Fatal error : mmap %p\n", this->map ) );
	}

	// Copio l'indirizzo relativo al controller gpio
	this->addr = (volatile uint32_t *) this->map;
}

gpio::~gpio() {

	// Rimuovo il mapping del controller gpio
	munmap( this->map, BLOCK_SIZE );

	// Chiudo `/dev/mem`
    close( this->mem_fd );
}

void
gpio::setup( uint8_t pin, PinMode mode, PullMode pud_mode ) {

	// Abilito/disabilito la resistenza di pull-up/down su tutti i pin
	if ( mode == INPUT ) this->setPullUpDown( pin, pud_mode );

	// Calcolo la posizione dei bit relativi al pin
	uint8_t shift = ( pin % 10 ) * 3;

	// Ricavo il registro che contiene il bit
	uint32_t &reg = *( this->map + GPFSEL0 + ( pin / 10 ) );

	// Imposto la modalità scelta per il pin
	// 000 = Input
	// 001 = Output
	reg = ( reg & ~( 7 << shift ) ) | ( (uint32_t) mode << shift );
}

void
gpio::setPullUpDown( uint8_t pin, PullMode mode ) {

	// Ricavo i due registri necessari
	uint32_t &reg_pullupdown = *( this->map + GPPUD0 );
	uint32_t &reg_clock = *( this->map + GPPUDCLK0 + ( pin / 32 ) );

	// Abilito/disabilito la resistenza di pull-up/down su tutti i pin
	// 00 = Pull-up/down disabilitato
	// 01 = Pull-down abilitato
	// 10 = Pull-up abilitato
	// 11 = Riservato
	reg_pullupdown = (uint32_t) mode;

	// Aspetto 150 cicli    
    waitCycles( 150 );

	// Imposto il clock sul pin
	reg_clock = 1 << ( pin % 32 );

	// Aspetto 150 cicli    
    waitCycles( 150 );

	// Ripristino i registri
	reg_clock = 0;
	reg_pullupdown = 0;
}

void
gpio::print_register( uint8_t offset, uint8_t group_bits = 0 ) {

	// Disegno il contenuto di un registro (funzione di debug)
	for ( int i = 31; i >= 0; i-- ) {

		std::cout << this->getBit( offset, i );

		if ( ( i + 1 ) % 3 == 0 ) std::cout << " ";
	}

	std::cout << std::endl;
}

} // Chiudo il namespace di Rpi-hw

#endif
