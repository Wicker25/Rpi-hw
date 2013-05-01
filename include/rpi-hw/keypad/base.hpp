/* 
    Title --- keypad/base.hpp

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


#ifndef _RPI_HW_KEYPAD_BASE_HPP_
#define _RPI_HW_KEYPAD_BASE_HPP_

#include <vector>

#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>
#include <rpi-hw/utils.hpp>
#include <rpi-hw/time.hpp>

#include <rpi-hw/bitset.hpp>

#include <rpi-hw/mutex.hpp>
#include <rpi-hw/thread.hpp>

#include <rpi-hw/iface/base.hpp>
#include <rpi-hw/iface/input.hpp>

namespace rpihw { // Begin main namespace

/*!
	@namespace rpihw::keypad
	@brief Namespace of the keypads.
*/

namespace keypad { // Begin keypads namespace

/*!
	@class base
	@brief Generic keypad controller.
*/
class base {

public:

	/*!
		@brief Constructor method.
		@param[in] total Number of the input pins (not necessarily equal to the number of the buttons).
		@param[in] ... Sequence of `uint8_t` containing the GPIO pins.
	*/
	base( size_t total, ... );

	/*!
		@brief Constructor method.
		@param[in] total Number of the input pins (not necessarily equal to the number of the buttons).
		@param[in] pins Vector containing the GPIO pins.
	*/
	base( size_t total, const std::vector< uint8_t > &pins );

	//! Destructor method.
	virtual ~base();

	/*!
		@brief Returns a button state.
		@param[in] index The index position of the input pin.
		@return The state of the button.
	*/
	virtual bool state( size_t index ) const;

	/*!
		@brief Checks if a button is pressed.
		@param[in] index The index position of the input pin.
		@return Return \c true if button is pressed.
	*/
	virtual bool pressed( size_t index ) const;

	/*!
		@brief Checks if a button is released.
		@param[in] index The index position of the input pin.
		@return Return \c true if button is released.
	*/
	virtual bool released( size_t index ) const;

	//! Returns the \ref bitset of button states.
	virtual const bitset &state() const;

	//! Returns the number of keys.
	virtual size_t numOfKeys() const;

protected:

	//! Buttons input interface.
	iface::input *m_input;

	//! Number of the keys.
	size_t m_nkeys;

	//! Button states (0 = up, 1 = down).
	bitset *m_keystate;

	//! Pressed buttons (0 = none, 1 = pressed).
	bitset *m_pressed;

	//! Pressed buttons (0 = none, 1 = released).
	bitset *m_released;

	//! Updating thread.
	thread< keypad::base > *m_thread;

	//! Mutex of the updating thread.
	mutex *m_mutex;

	//! Constructor method (only for child class)
	base();

	/*!
		@brief Initializes the interface.
		@param[in] total Number of the input pins (not necessarily equal to the number of the buttons).
		@param[in] pins Vector containing the GPIO pins.
	*/
	void init( size_t total, const std::vector< uint8_t > &pins );

	//! Updates the state of buttons (threading function).
	virtual void update();
};

} // End of keypads namespace

} // End of main namespace


// Include inline methods 
#include <rpi-hw/keypad/base-inl.hpp>

#endif /* _RPI_HW_KEYPAD_BASE_HPP_ */
