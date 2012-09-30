/* 
    Title --- gpio-inl.hpp

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


#ifndef _RPI_HW_GPIO_INL_HPP_
#define _RPI_HW_GPIO_INL_HPP_

namespace rpihw { // Namespace di Rpi-hw

inline void
gpio::setBit( uint8_t offset, uint8_t index, bool value ) {

	// Calcolo la posizione del bit
	uint8_t shift = ( index % 32 );

	// Ricavo il registro che contiene il bit
	uint32_t &reg = *( this->map + offset + ( index / 32 ) );

	// Imposto il valore di un bit su un registro a 32 bit
	reg = ( reg & ~( 1 << shift ) ) | ( value << shift );
}

inline bool
gpio::getBit( uint8_t offset, uint8_t index ) {

	// Ritorno il valore di un bit su un registro a 32 bit
	return *( this->map + offset + ( index / 32 ) ) & ( 1 << ( index % 32 ) ) > 0;
}

inline void
gpio::waitCycles( size_t cycles ) {

	// Aspetto un certo numero di cicli
    while ( cycles-- ) asm volatile( "nop" );
}

inline void
gpio::setup( uint8_t pin, PinMode mode ) {

	// Richiamo la funzione principale
	this->setup( pin, mode, PUD_OFF );
}

inline void
gpio::write( uint8_t pin, bool value ) {

	// Imposto il valore di un pin di uscita
	// 0 = Low
	// 1 = High
	*( this->map + ( value ? GPSET0 : GPCLR0 ) + ( pin / 32 ) ) = 1 << ( pin % 32 );
}

inline bool
gpio::read( uint8_t pin ) {

	// Ritorno il valore di un pin di ingresso
	// 0 = Low
	// 1 = High
	return this->getBit( GPLEV0, pin );
}

inline bool
gpio::getEvent( uint8_t pin ) {

	// Ritorno lo stato di un evento di un pin 
	// 0 = Nnessun evento rilevato sul pin
	// 1 = Evento rilevato sul pin
	return this->getBit( GPEDS0, pin );
}

inline void
gpio::setRisingEvent( uint8_t pin, bool value ) {

	// Abilito/disabilito l'evento di "risalita" del segnale su un pin
	// 0 = Non abilitato
	// 1 = Abilitato
	this->setBit( GPREN0, pin, value );
}

inline void
gpio::setFallingEvent( uint8_t pin, bool value ) {

	// Abilito/disabilito l'evento di "caduta" del segnale su un pin
	// 0 = Non abilitato
	// 1 = Abilitato
	this->setBit( GPFEN0, pin, value );
}

inline void
gpio::setHighEvent( uint8_t pin, bool value ) {

	// Abilito/disabilito l'evento del segnale "alto" su un pin
	// 0 = Non abilitato
	// 1 = Abilitato
	this->setBit( GPHEN0, pin, value );
}

inline void
gpio::setLowEvent( uint8_t pin, bool value ) {

	// Abilito/disabilito l'evento del segnale "basso" su un pin
	// 0 = Non abilitato
	// 1 = Abilitato
	this->setBit( GPLEN0, pin, value );
}

} // Chiudo il namespace di Rpi-hw

#endif
