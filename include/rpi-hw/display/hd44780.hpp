/* 
    Title --- display/hd44780.hpp

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


#ifndef _RPI_HW_DISPLAY_HD44780_HPP_
#define _RPI_HW_DISPLAY_HD44780_HPP_

#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>
#include <rpi-hw/math.hpp>
#include <rpi-hw/utils.hpp>

#include <rpi-hw/iface/base.hpp>
#include <rpi-hw/iface/output.hpp>
#include <rpi-hw/iface/input.hpp>

namespace rpihw { // Begin main namespace

namespace display { // Begin displays namespace

/* HITACHI HD44780 LCD CONTROLLER */
/*!
	@class hd44780
	@brief Hitachi HD44780 LCD controller.

	@example lcd16x2.cpp
	@example lcd20x4demo.cpp
*/
class hd44780 {

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

	//! The custom characters.
	enum CustomCharacters {

		CCHAR0 = 0,
		CCHAR1 = 1,
		CCHAR2 = 2,
		CCHAR3 = 3,
		CCHAR4 = 4,
		CCHAR5 = 5,
		CCHAR6 = 6,
		CCHAR7 = 7
	};

	//! The cursor modes (bitwise flags).
	enum CursorMode {

		NO_CURSOR		= 0x00,		//!< No cursor.
		CURSOR_SOLID	= 0x01,		//!< Solid cursor.
		CURSOR_BLINKING	= 0x02		//!< Blinking the cursor.
	};

	//! The autoscroll modes (bitwise flags).
	enum AutoscrollMode {

		NO_SCROLL		= 0x00,		//!< No scroll.
		VSCROLL			= 0x01,		//!< Vertical scroll.
		HSCROLL			= 0x02,		//!< Horizontal scroll.
		HSCROLL_LINE	= 0x04		//!< Horizontal scroll line.
	};

	//! DDRAM line addresses
	static const uint8_t lines[4];

	/*!
		@brief Constructor method (4-bit mode).
		@param[in] rs The GPIO pin connected to the rs pin.
		@param[in] e The GPIO pin connected to the e pin.
		@param[in] d0 The GPIO pin connected to the d0 pin.
		@param[in] d1 The GPIO pin connected to the d1 pin.
		@param[in] d2 The GPIO pin connected to the d2 pin.
		@param[in] d3 The GPIO pin connected to the d3 pin.
	*/
	hd44780( uint8_t rs, uint8_t e,
			 uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3 );

	/*!
		@brief Constructor method (8-bit mode).
		@param[in] rs The GPIO pin connected to the rs pin.
		@param[in] e The GPIO pin connected to the e pin.
		@param[in] d0 The GPIO pin connected to the d0 pin.
		@param[in] d1 The GPIO pin connected to the d1 pin.
		@param[in] d2 The GPIO pin connected to the d2 pin.
		@param[in] d3 The GPIO pin connected to the d3 pin.
		@param[in] d4 The GPIO pin connected to the d4 pin.
		@param[in] d5 The GPIO pin connected to the d5 pin.
		@param[in] d6 The GPIO pin connected to the d6 pin.
		@param[in] d7 The GPIO pin connected to the d7 pin.
	*/
	hd44780( uint8_t rs, uint8_t e,
			 uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
			 uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7 );

	//! Destructor method.
	virtual ~hd44780();

	/*!
		@brief Initializes the display.
		@param[in] cols Number of the display columns.
		@param[in] rows Number of the display rows.
		@param[in] font If \c true uses 5x10 dots font, else uses 5x8 dots font.
	*/
	virtual void init( uint8_t cols, uint8_t rows, bool font = 0 );

	/*!
		@brief Sends a command to the display.
		@param[in] data The command.
	*/
	virtual void cmd( uint8_t data );

	/*!
		@brief Writes a character on the display (low level).
		@param[in] chr The 8-bit character.
	*/
	virtual void putchar( uint8_t chr );

	/*!
		@brief Reads a character from the buffer at specified position.
		@param[in] x The x-position of the character.
		@param[in] y The y-position of the character.
		@return The 8-bit character at position.
	*/
	virtual uint8_t getChar( uint8_t x, uint8_t y ) const;

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

	//! Moves the cursor to the new line.
	virtual void newLine();

	/*!
		@brief Writes a character on the display.
		@param[in] chr The 8-bit character.
	*/
	virtual void write( uint8_t chr );

	/*!
		@brief Moves the cursor position and writes a character on the display.
		@param[in] x The new x-position of the cursor.
		@param[in] y The new y-position of the cursor.
		@param[in] chr The 8-bit character.
	*/
	virtual void write( uint8_t x, uint8_t y, uint8_t chr );

	/*!
		@brief Writes a string on the display.
		@param[in] text The string to be written.
		@param[in] delay The delay time between a letter and another in milliseconds.
	*/
	virtual void write( const std::string &text, size_t delay = 0 );

	/*!
		@brief Moves the cursor position and writes a string on the display.
		@param[in] x The new x-position of the cursor.
		@param[in] y The new y-position of the cursor.
		@param[in] text The string to be written.
		@param[in] delay The delay time between a letter and another in milliseconds.
	*/
	virtual void write( uint8_t x, uint8_t y, const std::string &text, size_t delay = 0 );

	/*!
		@brief Scrolls the contents of the display to the left.
		@param[in] cursor If \c true, will also moves the cursor.
	*/
	virtual void scrollLeft( bool cursor = 1 );

	/*!
		@brief Scrolls the contents of the display to the right.
		@param[in] cursor If \c true, will also moves the cursor.
	*/
	virtual void scrollRight( bool cursor = 1 );

	/*!
		@brief Scrolls the contents of the display to the up.
		@param[in] cursor If \c true, will also moves the cursor.
	*/
	virtual void scrollUp( bool cursor = 1 );

	/*!
		@brief Scrolls the contents of the display to the down.
		@param[in] cursor If \c true, will also moves the cursor.
	*/
	virtual void scrollDown( bool cursor = 1 );

	/*!
		@brief Scrolls a line to the left.
		@param[in] line The number of the line to be moved.
		@param[in] cursor If \c true, will also moves the cursor.
	*/
	virtual void scrollLeftLine( uint8_t line, bool cursor = 1 );

	/*!
		@brief Scrolls a line to the right.
		@param[in] line The number of the line to be moved.
		@param[in] cursor If \c true, will also moves the cursor.
	*/
	virtual void scrollRightLine( uint8_t line, bool cursor = 1 );

	/*!
		@brief Defines a custom character.
		@param[in] index The index position of the custom character.
		@param[in] data The array containing the character's pixel data (an element per row).
	*/
	virtual void defChar( uint8_t index, const uint8_t *data );

	/*!
		@brief Sets the cursor mode.
		@param[in] mode The bitwise flags of the cursor mode. You can use \c NO_CURSOR, \c CURSOR_SOLID and \c CURSOR_BLINKING.
	*/
	virtual void setCursor( uint8_t mode );

	/*!
		@brief Sets the autoscroll mode.
		@param[in] mode The bitwise flags of the autoscroll mode. You can use \c NO_SCROLL, \c VSCROLL, \c HSCROLL and \c HSCROLL_LINE.
	*/
	virtual void setAutoscroll( uint8_t mode );

protected:

	//! Output interface to control pins.
	iface::output *m_mode;

	//! Output interface to data pins.
	iface::output *m_data;

	//! Number of the display columns.
	uint8_t m_cols;

	//! Number of the display rows.
	uint8_t m_rows;

	//! Number of the characters.
	size_t m_size;

	//! Font height.
	uint8_t m_font_height;

	//! Text buffer.
	uint8_t *m_buffer;

	//! Cursor position.
	struct { uint8_t x, y; } m_pos;

	//! Autoscroll mode.
	uint8_t m_autoscroll;

	//! Toggles the enable pin.
	void strobe();

	/*!
		@brief Sends a nibble data to the display.
		@param[in] data The 4-bit data to be sended.
		@param[in] delay The delay time after the sending of the data.
	*/
	virtual void send( uint8_t data, size_t delay = 0 );

	/*!
		@brief Sends a serial data to the display (a nibble at a time).
		@param[in] data The 8-bit data to be sended.
		@param[in] delay The delay time after the sending of the data.
	*/
	virtual void sendSerial( uint8_t data, size_t delay = 0 );

	//! Checks if the current line is full
	virtual bool isLineFull();
};

} // End of displays namespace

} // End of main namespace

#endif
