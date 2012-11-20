/* 
    Title --- keypad/base.hpp

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


#ifndef _RPI_HW_KEYPAD_BASE_HPP_
#define _RPI_HW_KEYPAD_BASE_HPP_

#include <vector>

#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>
#include <rpi-hw/utils.hpp>

#include <rpi-hw/bitset.hpp>

#include <rpi-hw/mutex.hpp>
#include <rpi-hw/thread.hpp>

#include <rpi-hw/iface/base.hpp>
#include <rpi-hw/iface/input.hpp>

namespace rpihw { // Begin main namespace

namespace keypad { // Begin keypads namespace

/* KEYPAD CONTROLLER BASE CLASS */
class base {

public:

	// Constructor and destructor methods
	base();
	base( size_t total, ... );
	base( size_t total, const std::vector< uint8_t > &pins );
	virtual ~base();

	// Returns a button state
	virtual bool state( size_t index ) const;
	// Checks if a button is pressed
	virtual bool pressed( size_t index ) const;
	// Checks if a button is released
	virtual bool released( size_t index ) const;
	// Returns the bitset of button states
	virtual const bitset &state() const;
	// Returns the number of keys
	virtual size_t numOfKeys() const;

protected:

	// Buttons input interface
	iface::input *m_input;

	// Number of keys
	size_t m_nkeys;

	// Button registers
	bitset *m_keystate, *m_pressed, *m_released;

	// Updating thread and mutex
	thread< keypad::base > *m_thread;
	mutex *m_mutex;

	// Initializes the interface
	void init( size_t total, const std::vector< uint8_t > &pins );

	// Updates the state of buttons
	virtual void update();
};

} // End of keypads namespace

} // End of main namespace

#endif
