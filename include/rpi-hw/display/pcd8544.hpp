/* 
    Title --- display/pcd8544.hpp

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


#ifndef _RPI_HW_DISPLAY_PCD8544_HPP_
#define _RPI_HW_DISPLAY_PCD8544_HPP_

#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>
#include <rpi-hw/math.hpp>
#include <rpi-hw/utils.hpp>

#include <rpi-hw/iface/base.hpp>
#include <rpi-hw/iface/output.hpp>
#include <rpi-hw/iface/input.hpp>

namespace rpihw { // Begin main namespace

namespace display { // Begin displays namespace

/* PHILIPS PCD8544 LCD CONTROLLER */
/*!
	@class pcd8544
	@brief Philips PCD8544 LCD controller.
*/
class pcd8544 {

public:

	//! The controller command set.
	enum CommandSet {

		CLEAR	= 0x01,		//!< Clear display.
		HOME	= 0x02,		//!< Cursor home.
		ENTRY	= 0x04,		//!< Entry mode set.
		POWER	= 0x08,		//!< Display on/off control.
		SHIFT	= 0x10,		//!< Cursor/display shift.
		FUNC	= 0x20,		//!< Function set.
		CGRAM	= 0x40,		//!< Set CGRAM address.
		DGRAM	= 0x80		//!< Set DDRAM address.
	};

	//! The controller command set (bit flags).
	enum CommandArgs {

		ENTRY_ID	= 0x02,		//!< Increments the cursor after each byte written to display.
		ENTRY_S		= 0x01,		//!< Shifts display when byte written to display.

		POWER_D		= 0x04,		//!< Turns on the display (else turn off).
		POWER_C		= 0x02,		//!< Turns on the cursor (else turn off).
		POWER_B		= 0x01,		//!< Sets a blinking cursor (else sets a solid cursor).

		SHIFT_SC	= 0x08,		//!< Sets display-shift (else sets cursor-move).
		SHIFT_RL	= 0x04,		 //!< Sets cursor shift direction to right (else to left).

		FUNC_DL		= 0x10,		//!< Sets the 8 bit mode (else sets the 4 bit mode).
		FUNC_N		= 0x08,		//!< Sets number of display lines to 2/4 (else 1).
		FUNC_F		= 0x04		//!< Sets the 5x10 character font (else 5x8).
	};


	//! FIXME FIXME FIXME
	//! FIXME FIXME FIXME
	//! FIXME FIXME FIXME
	//! FIXME FIXME FIXME
	enum DataPin {

		SCLK	= 0,
		SDIN	= 1,
		DC		= 2,
		SCE		= 3,
		RESET	= 4
	};


	//! The size of the display.
	enum DisplaySize {

		LCD_WIDTH	= 84,
		LCD_HEIGHT	= 48
	};

	/*!
		@brief Constructor method (4-bit mode).
		@param[in] sclk The GPIO pin connected to the sclk pin.
		@param[in] sda The GPIO pin connected to the sda pin.
		@param[in] dorc The GPIO pin connected to the dorc pin.
		@param[in] cs The GPIO pin connected to the cs pin.
		@param[in] reset The GPIO pin connected to the reset pin.
	*/
	pcd8544( uint8_t sclk, uint8_t sdin, uint8_t dc, uint8_t sce, uint8_t reset );

	//! Destructor method.
	virtual ~pcd8544();

	/*!
		@brief Initializes the display.
		@param[in] cols Number of the display columns.
		@param[in] rows Number of the display rows.
		@param[in] font If \c true uses 5x10 dots font, else uses 5x8 dots font.
	*/
	virtual void init();

	/*!
		@brief Sends a command to the display.
		@param[in] data The command.
	*/
	virtual void cmd( uint8_t data );

	//! Homes the cursor.
	virtual void home();

	//! Clears the screen.
	virtual void clear();

	/*!
		@brief Sets the position of the cursor on the display.
		@param[in] x The new x-position of the cursor.
		@param[in] y The new y-position of the cursor.
	*/
	virtual void move( uint8_t x, uint8_t y );

	/*!
		@brief Writes a character on the display.
		@param[in] chr The 8-bit character.
	*/
	virtual void write( uint8_t chr );

protected:

	//! Output interface to data pins.
	iface::output *m_data;

	//! Cursor position.
	uint8_t m_pos[2];

	/*!
		@brief Sends a nibble data to the display.
		@param[in] data The 4-bit data to be sended.
		@param[in] delay The delay time after the sending of the data.
	*/
	virtual void send( uint8_t data );
};

} // End of displays namespace

} // End of main namespace

#endif
