/* 
    Title --- keypad/base.cpp

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


#ifndef _RPI_HW_KEYPAD_BASE_CPP_
#define _RPI_HW_KEYPAD_BASE_CPP_

#include <rpi-hw/keypad/base.hpp>

#include <rpi-hw/utils.hpp>
#include <rpi-hw/utils-inl.hpp>

#include <rpi-hw/bitset.hpp>
#include <rpi-hw/bitset-inl.hpp>

#include <rpi-hw/mutex.hpp>
#include <rpi-hw/mutex-inl.hpp>

#include <rpi-hw/thread.hpp>
#include <rpi-hw/thread-inl.hpp>

#include <rpi-hw/gpio.hpp>
#include <rpi-hw/gpio-inl.hpp>

#include <rpi-hw/iface/base.hpp>
#include <rpi-hw/iface/base-inl.hpp>

#include <rpi-hw/iface/input.hpp>
#include <rpi-hw/iface/input-inl.hpp>

#include <rpi-hw/keypad/base-inl.hpp>

namespace rpihw { // Begin main namespace

namespace keypad { // Begin keypads namespace

base::base() {

}

base::base( size_t total, ... ) {

	// Initialize variable argument list
	va_list args;
	va_start( args, total );

	// Initialize the instance
	init( total, utils::varg< uint8_t, int >( args, total ) );

	// Clean variable argument list
	va_end( args );
}

base::base( size_t total, const std::vector< uint8_t > &pins ) {

	// Initialize the instance
	init( total, pins );
}

base::~base() {

	// Destroy the updating thread and mutex
	delete m_thread;
	delete m_mutex;

	// Destroy the input interface
	delete m_input;

	// Destroy the button registers
	delete m_keystate;
	delete m_pressed;
	delete m_released;
}

void
base::init( size_t total, const std::vector< uint8_t > &pins ) {

	// Store the number of keys
	m_nkeys = total;

	// Create the button registers
	m_keystate	= new bitset( m_nkeys, 0 );
	m_pressed	= new bitset( m_nkeys, 0 );
	m_released	= new bitset( m_nkeys, 0 );

	// Create the buttons input interface
	m_input = new iface::input( pins );

	// Create the updating thread and mutex
	m_thread = new thread< keypad::base >( *this, &keypad::base::update );
	m_mutex = new mutex;
}

bool
base::state( size_t index ) const {

	// Check if the button exists
	if ( index >= m_nkeys )
		throw exception( utils::format( "(Error) `keypad::state`: keypad %p has only %lu buttons\n",
										this, (unsigned long) m_nkeys ) );

	// Return the button state
	return m_keystate->get( index );
}

bool
base::pressed( size_t index ) const {

	// Check if the button exists
	if ( index >= m_nkeys )
		throw exception( utils::format( "(Error) `keypad::pressed`: keypad %p has only %lu buttons\n",
										this, (unsigned long) m_nkeys ) );

	// Return `true` if the button is pressed
	return m_pressed->get( index );
}

bool
base::released( size_t index ) const {

	// Check if the button exists
	if ( index >= m_nkeys )
		throw exception( utils::format( "(Error) `keypad::released`: keypad %p has only %lu buttons\n",
										this, (unsigned long) m_nkeys ) );

	// Return `true` if the button is released
	return m_released->get( index );
}

void
base::update() {

	// Working structures
	size_t state;

	// Iterators
	uint8_t i;

	// Updating loop
	while ( 1 ) {

		// Update state of buttons
		for ( i = 0; i < m_nkeys; i++ ) {

			// Read the state of i-th button
			state = m_input->read( i );

			// Update the button registers
			m_mutex->lock();

			m_pressed->set( i, !m_keystate->get( i ) && state );
			m_released->set( i, m_keystate->get( i ) && !state );
			m_keystate->set( i, state );

			m_mutex->unlock();
		}

		// Wait some time (100 ms)
		utils::msleep( 100 );
	}
}

} // End of keypads namespace

} // End of main namespace

#endif
