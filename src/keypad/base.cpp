/* 
    Title --- keypad/base.cpp

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


#ifndef _RPI_HW_KEYPAD_BASE_CPP_
#define _RPI_HW_KEYPAD_BASE_CPP_

#include <rpi-hw/keypad/base.hpp>

namespace rpihw { // Begin main namespace

namespace keypad { // Begin keypads namespace

base::base( size_t total, std::initializer_list< uint8_t > pins )

	: m_nkeys		( total )
	, m_input		( new iface::input( pins, PULL_UP ) )
	, m_keystate	( m_nkeys, 0 )
	, m_pressed		( m_nkeys, 0 )
	, m_released	( m_nkeys, 0 )
	, m_frequency	( 10.0 )
	, m_thread		( new std::thread( &keypad::base::update, this ) )
	, m_mutex		( new std::mutex ) {

}

base::base( size_t total, std::initializer_list< uint8_t > pins, const std::vector< uint8_t > &keymap )

	: m_nkeys		( total )
	, m_input		( new iface::input( pins, PULL_UP ) )
	, m_keystate	( m_nkeys, 0 )
	, m_pressed		( m_nkeys, 0 )
	, m_released	( m_nkeys, 0 )
	, m_frequency	( 10.0 )
	, m_thread		( new std::thread( &keypad::base::update, this ) )
	, m_mutex		( new std::mutex ) {

	// Set the keymap
	setKeymap( keymap );
}

base::base( size_t total, const std::vector< uint8_t > &pins )

	: m_nkeys		( total )
	, m_input		( new iface::input( pins, PULL_UP ) )
	, m_keystate	( m_nkeys, 0 )
	, m_pressed		( m_nkeys, 0 )
	, m_released	( m_nkeys, 0 )
	, m_frequency	( 10.0 )
	, m_thread		( new std::thread( &keypad::base::update, this ) )
	, m_mutex		( new std::mutex ) {

}

base::base( size_t total, const std::vector< uint8_t > &pins, const std::vector< uint8_t > &keymap )

	: m_nkeys		( total )
	, m_input		( new iface::input( pins, PULL_UP ) )
	, m_keystate	( m_nkeys, 0 )
	, m_pressed		( m_nkeys, 0 )
	, m_released	( m_nkeys, 0 )
	, m_frequency	( 10.0 )
	, m_thread		( new std::thread( &keypad::base::update, this ) )
	, m_mutex		( new std::mutex ) {

	// Set the keymap
	setKeymap( keymap );
}

base::~base() {

	// Destroy the interfaces
	delete m_input;

	// Destroy the thread and mutex instances 
	delete m_thread;
	delete m_mutex;
}

void
base::setKeymap( const std::vector< uint8_t > &keymap ) {

	// Check the keymap
	if ( keymap.size() != m_nkeys )
		throw exception( utils::format( "(Fatal) `keypad::setKeymap`: bad keymap\n" ) );

	// Store the keymap
	uint8_t index = 0;

	for ( auto &key : keymap )
		m_keymap[ key ] = index++;
}

bool
base::state( size_t index ) const {

	// Check if the button exists
	if ( index >= m_nkeys )
		throw exception( utils::format( "(Fatal) `keypad::state`: keypad %p has only %lu buttons\n",
										this, (unsigned long) m_nkeys ) );

	// Return the button state
	return m_keystate[ index ];
}

bool
base::pressed( size_t index ) const {

	// Check if the button exists
	if ( index >= m_nkeys )
		throw exception( utils::format( "(Fatal) `keypad::pressed`: keypad %p has only %lu buttons\n",
										this, (unsigned long) m_nkeys ) );

	// Return `true` if the button is pressed
	return m_pressed[ index ];
}

bool
base::released( size_t index ) const {

	// Check if the button exists
	if ( index >= m_nkeys )
		throw exception( utils::format( "(Fatal) `keypad::released`: keypad %p has only %lu buttons\n",
										this, (unsigned long) m_nkeys ) );

	// Return `true` if the button is released
	return m_released[ index ];
}

bool
base::keyState( uint8_t key ) const {

	// Check if the key exists
	T_Keymap::const_iterator it = m_keymap.find( key );

	if ( it == m_keymap.end() )
		throw exception( utils::format( "(Fatal) `keypad::state`: keypad %p doesn't have key '%c'\n",
										this, (char) key ) );

	// Return the button state
	return m_keystate[ it->second ];
}

bool
base::keyPressed( uint8_t key ) const {

	// Check if the key exists
	T_Keymap::const_iterator it = m_keymap.find( key );

	if ( it == m_keymap.end() )
		throw exception( utils::format( "(Fatal) `keypad::pressed`: keypad %p doesn't have key '%c'\n",
										this, (char) key ) );

	// Return `true` if the button is pressed
	return m_pressed[ it->second ];
}

bool
base::keyReleased( uint8_t key ) const {

	// Check if the key exists
	T_Keymap::const_iterator it = m_keymap.find( key );

	if ( it == m_keymap.end() )
		throw exception( utils::format( "(Fatal) `keypad::released`: keypad %p doesn't have key '%c'\n",
										this, (char) key ) );

	// Return `true` if the button is released
	return m_released[ it->second ];
}

std::vector< uint8_t >
base::keyState() const {

	// List of pressed keys
	std::vector< uint8_t > keys;
	keys.reserve( m_nkeys );

	// Find pressed keys
	for ( auto &key : m_keymap )
		if ( m_keystate[ key.second ] )
			keys.push_back( key.first );

	// Return the list of pressed keys
	return keys;
}

} // End of keypads namespace

} // End of main namespace

#endif /* _RPI_HW_KEYPAD_BASE_CPP_ */
