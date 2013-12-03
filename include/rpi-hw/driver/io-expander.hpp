/* 
	Title --- driver/io-expander.hpp

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


#ifndef _RPI_HW_DRIVER_IO_EXPANDER_HPP_
#define _RPI_HW_DRIVER_IO_EXPANDER_HPP_

#include <rpi-hw/rpi.hpp>

#include <rpi-hw/consts.hpp>
#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>
#include <rpi-hw/utils.hpp>

namespace rpihw { // Begin main namespace

namespace driver { // Begin drivers namespace

/*!
	@class io_expander
	@brief GPIO controller.
*/
class io_expander {

public:

	/*!
		@brief Sets the mode of a GPIO pin.
		@param[in] pin The GPIO pin.
		@param[in] mode The GPIO mode.
		@param[in] pull_mode The pull resistor mode.
	*/
	virtual void setup( uint8_t pin, uint8_t mode, uint8_t pull_mode = PULL_OFF );

	/*!
		@brief Sets the value of a output pin.
		@param[in] pin The output pin.
		@param[in] value The value of output pin.
	*/
	virtual void write( uint8_t pin, bool value );

	/*!
		@brief Returns the value of a input pin.
		@param[in] pin The input pin.
		@return The value of input pin.
	*/
	virtual bool read( uint8_t pin );

	/*!
		@brief Returns the event state of a GPIO pin.
		@param[in] pin The GPIO pin.
		@return The event state.
	*/
	virtual bool checkEvent( uint8_t pin );

	/*!
		@brief Enables/disables the rising edge event on a GPIO pin.
		@param[in] pin The GPIO pin.
		@param[in] enabled If \c true enable the rising edge event.
	*/
	virtual void setRisingEvent( uint8_t pin, bool enabled );

	/*!
		@brief Enables/disables the falling edge event on a GPIO pin.
		@param[in] pin The GPIO pin.
		@param[in] enabled If \c true enable the falling edge event.
	*/
	virtual void setFallingEvent( uint8_t pin, bool enabled );

	/*!
		@brief Enables/disables the high event on a GPIO pin.
		@param[in] pin The GPIO pin.
		@param[in] enabled If \c true enable the high event.
	*/
	virtual void setHighEvent( uint8_t pin, bool enabled );

	/*!
		@brief Enables/disables the low event on a GPIO pin.
		@param[in] pin The GPIO pin.
		@param[in] enabled If \c true enable the low event.
	*/
	virtual void setLowEvent( uint8_t pin, bool enabled );

	/*!
		@brief Enables/disables the pull-up/down control on a GPIO pin.
		@param[in] pin The GPIO pin.
		@param[in] mode The pull resistor mode.
	*/
	virtual void setPullUpDown( uint8_t pin, uint8_t mode );
};

} // End of drivers namespace

} // End of main namespace


// Include inline methods 
#include <rpi-hw/driver/io-expander-inl.hpp>

#endif /* _RPI_HW_DRIVER_IO_EXPANDER_HPP_ */
