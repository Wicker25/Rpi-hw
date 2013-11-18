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

#include <functional>
#include <vector>
#include <map>

#include <thread>
#include <mutex>

#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>
#include <rpi-hw/math.hpp>
#include <rpi-hw/time.hpp>

#include <rpi-hw/iface/base.hpp>
#include <rpi-hw/iface/input.hpp>

namespace rpihw { // Begin main namespace

/*!
	@namespace rpihw::keypad
	@brief Namespace of the keypads.
*/

namespace keypad { // Begin keypads namespace

// Prototypes
class base;

//! The type of the keypad event listener.
typedef std::function< void ( keypad::base & ) > T_EventListener;

/*!
	@class base
	@brief Generic keypad controller.
*/
class base {

public:

	//! The keymap type.
	typedef std::map< uint8_t, uint8_t > T_Keymap;

	/*!
		@brief Constructor method.
		@param[in] total Number of the buttons.
		@param[in] pins Sequence of `uint8_t` containing the input GPIOs.
	*/
	base( size_t total, std::initializer_list< uint8_t > pins );

	/*!
		@brief Constructor method.
		@param[in] total Number of the buttons.
		@param[in] pins Sequence of `uint8_t` containing the input GPIOs.
		@param[in] keymap The keymap vector.
	*/
	base( size_t total, std::initializer_list< uint8_t > pins, const std::vector< uint8_t > &keymap );

	/*!
		@brief Constructor method.
		@param[in] total Number of the buttons.
		@param[in] pins Vector containing the input GPIO pins.
	*/
	base( size_t total, const std::vector< uint8_t > &pins );

	/*!
		@brief Constructor method.
		@param[in] total Number of the buttons.
		@param[in] pins Vector containing the input GPIO pins.
		@param[in] keymap The keymap vector.
	*/
	base( size_t total, const std::vector< uint8_t > &pins, const std::vector< uint8_t > &keymap );

	//! Destructor method.
	virtual ~base();

	/*!
		@brief Sets the keymap.
		@param[in] keymap The keymap vector.
	*/
	virtual void setKeymap( const std::vector< uint8_t > &keymap );

	/*!
		@brief Sets the keypad event listener.
		@param[in] listener The event listener.
	*/
	virtual void addEventListener( T_EventListener listener );

	/*!
		@brief Sets the frequency with which buttons are read.
		@param[in] frequency The refresh rate in Hz.
	*/
	virtual void setRefreshRate( float frequency );

	//! Returns the frequency with which buttons are read.
	virtual float getRefreshRate() const;

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

	//! Returns the list of button states.
	virtual const std::vector< bool > &state() const;

	/*!
		@brief Returns a key state.
		@param[in] key The key button.
		@return The state of the button.
	*/
	virtual bool keyState( uint8_t key ) const;

	/*!
		@brief Checks if a key is pressed.
		@param[in] key The key button.
		@return Return \c true if button is pressed.
	*/
	virtual bool keyPressed( uint8_t key ) const;

	/*!
		@brief Checks if a key is released.
		@param[in] key The key button.
		@return Return \c true if button is released.
	*/
	virtual bool keyReleased( uint8_t key ) const;

	//! Returns the list of pressed keys.
	virtual std::vector< uint8_t > keyState() const;

	//! Returns the number of keys.
	virtual size_t numOfKeys() const;

protected:

	//! Number of the keys.
	size_t m_nkeys;

	//! Buttons input interface.
	iface::input *m_input;

	//! The keymap vector.
	T_Keymap m_keymap;

	//! Button states (0 = up, 1 = down).
	std::vector< bool > m_keystate;

	//! Pressed buttons (0 = none, 1 = pressed).
	std::vector< bool > m_pressed;

	//! Pressed buttons (0 = none, 1 = released).
	std::vector< bool > m_released;

	//! The refresh rate.
	float m_frequency;

	//! Updating thread.
	std::thread *m_thread;

	//! Mutex of the updating thread.
	std::mutex *m_mutex;

	//! The keypad event listener.
	T_EventListener m_event_listener;

	//! Updates the state of buttons (threading function).
	virtual void update();
};

} // End of keypads namespace

} // End of main namespace


// Include inline methods 
#include <rpi-hw/keypad/base-inl.hpp>

#endif /* _RPI_HW_KEYPAD_BASE_HPP_ */
