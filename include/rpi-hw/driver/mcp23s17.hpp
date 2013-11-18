/* 
	Title --- driver/mcp23s17.hpp

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


#ifndef _RPI_HW_DRIVER_MCP23S17_HPP_
#define _RPI_HW_DRIVER_MCP23S17_HPP_

#include <rpi-hw/rpi.hpp>

#include <rpi-hw/consts.hpp>
#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>
#include <rpi-hw/utils.hpp>

#include <rpi-hw/driver/spi.hpp>
#include <rpi-hw/driver/ioexpander.hpp>

namespace rpihw { // Begin main namespace

namespace driver { // Begin drivers namespace

/*!
	@class mcp23s17
	@brief 16-Bit I/O Expander with SPI.
*/
class mcp23s17 : public ioexpander {

public:

	//! The controller command set.
	enum Commands {

		WRITE	= 0x40,	//!< Writes on the register.
		READ	= 0x41	//!< Reads from the register.
	};

	//! Device registers.
	enum Registers {

		IODIR		= 0x00,	//!< Controls the direction of the data I/O.
		IPOL		= 0x02,	//!< Configures the polarity on the corresponding GPIO port bits.
		GPINTEN		= 0x04,	//!< Controls the interrupt-on-change feature for each pin
		DEFVAL		= 0x06,	//!< Sets the default comparison value.
		INTCON		= 0x08, //!< Controls how the associated pin value is compared for the interrupt-on-change feature.
		IOCON		= 0x0a,	//!< Configures the device.
		GPPU		= 0x0c,	//!< Controls the pull-up resistors for the port pins.
		INTF		= 0x0e,	//!< Reflects the interrupt condition on the port pins of any pin that is enabled for interrupts.
		INTCAP		= 0x10,	//!< Captures the GPIO port value at the time the interrupt occurred.
		GPIO		= 0x12,	//!< Reflects the value on the port.
		OLAT		= 0x14,	//!< Provides access to the output latches.
	};

	//! The controller configuration set.
	enum Settings {

		INTPOL	= 0x02,	//!< Sets the polarity of the INT output pin
		ODR		= 0x04,	//!< Configures the INT pin as an open-drain output.
		HAEN	= 0x08,	//!< Hardware address enable.
		DISSLW	= 0x10,	//!< Slew Rate control bit for SDA output.
		SEQOP	= 0x20,	//!< Sequential operation mode.
		MIRROR	= 0x40,	//!< Pins mirror.
		BANK	= 0x80	//!< Controls how the registers are addressed.
	};

	/*!
		@brief Constructor method.
		@param[in] dev_path The device path.
		@param[in] device_id The device identifier.
	*/
	mcp23s17( const std::string &dev_path, uint8_t device_id = 0 );

	//! Destructor method.
	virtual ~mcp23s17();

	/*!
		@brief Sets the mode of a GPIO pin.
		@param[in] pin The GPIO pin.
		@param[in] mode The GPIO mode.
		@param[in] pud_mode The pull resistor mode.
	*/
	virtual void setup( uint8_t pin, uint8_t mode, uint8_t pud_mode = PUD_OFF );

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
		@brief Enables/disables the pull-up control on a GPIO pin.
		@param[in] pin The GPIO pin.
		@param[in] mode The pull resistor mode.
	*/
	virtual void setPullUpDown( uint8_t pin, uint8_t mode );

private:

	//! Serial Peripheral Interface.
	driver::spi *m_spi;

	//! Data buffer containing the state of the GPIOs.
	uint8_t m_states[6];

	//! Data buffer used for SPI transmission.
	uint8_t m_buffer[3];

	//! Device identifier.
	uint8_t m_device_id;

	//! Sends data to the device.
	void send( uint8_t reg, uint8_t data );

	//! Receives data from the device.
	uint8_t receive( uint8_t reg );
};

} // End of drivers namespace

} // End of main namespace


// Include inline methods 
#include <rpi-hw/driver/mcp23s17-inl.hpp>

#endif /* _RPI_HW_DRIVER_MCP23S17_HPP_ */
