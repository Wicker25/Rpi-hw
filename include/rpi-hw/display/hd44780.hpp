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
class hd44780 {

public:

	// Constants
	enum CommandSet {

		CLEAR	= 0x01,	// Clear display
		HOME	= 0x02,	// Cursor home
		ENTRY	= 0x04,	// Entry mode set
		POWER	= 0x08,	// Display on/off control
		SHIFT	= 0x10,	// Cursor/display shift
		FUNC	= 0x20,	// Function set
		CGRAM	= 0x40,	// Set CGRAM address
		DGRAM	= 0x80	// Set DDRAM address
	};

	enum CommandArgs {

		ENTRY_ID	= 0x02,	// Increments the cursor after each byte written to display
		ENTRY_S		= 0x01,	// Shifts display when byte written to display

		POWER_D		= 0x04,	// Turns on the display (else turn off)
		POWER_C		= 0x02,	// Turns on the cursor (else turn off)
		POWER_B		= 0x01,	// Sets a blinking cursor (else sets a solid cursor)

		SHIFT_SC	= 0x08,	// Sets display-shift (else sets cursor-move)
		SHIFT_RL	= 0x04, // Sets cursor shift direction to right (else to left)

		FUNC_DL		= 0x10,	// Sets the 8 bit mode (else sets the 4 bit mode)
		FUNC_N		= 0x08,	// Sets number of display lines to 2/4 (else 1)
		FUNC_F		= 0x04	// Sets the 5x10 character font (else 5x8)
	};

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

	enum CursorMode {

		NO_CURSOR		= 0x00,
		CURSOR_SOLID	= 0x01,
		CURSOR_BLINKING	= 0x02
	};

	enum AutoscrollMode {

		NO_SCROLL		= 0x00,
		VSCROLL			= 0x01,
		HSCROLL			= 0x02,
		HSCROLL_LINE	= 0x04
	};

	// Address locations
	static const uint8_t lines[4];

	// Constructor and destructor methods
	hd44780( uint8_t rs, uint8_t e,
			 uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3 );

	hd44780( uint8_t rs, uint8_t e,
			 uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
			 uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7 );

	virtual ~hd44780();

	// Initializes the display
	virtual void init( uint8_t cols, uint8_t rows, bool font = 0 );
	// Sends a command to the display
	virtual void cmd( uint8_t data );
	// Writes a character on the display (low level)
	virtual void putchar( uint8_t chr );
	// Reads a character from the buffer
	virtual uint8_t getChar( uint8_t x, uint8_t y ) const;

	// Homes the cursor
	virtual void home();
	// Clears the screen
	virtual void clear();
	// Sets the position of the cursor on the display
	virtual void move( uint8_t x, uint8_t y );
	// Moves the cursor to the new line
	virtual void newLine();

	// Writes a character on the display
	virtual void write( uint8_t chr );
	virtual void write( uint8_t x, uint8_t y, uint8_t chr );

	// Writes a string on the display
	virtual void write( const std::string &text, size_t delay = 0 );
	virtual void write( uint8_t x, uint8_t y, const std::string &text, size_t delay = 0 );

	// Scrolls the contents of the display to the left
	virtual void scrollLeft( bool cursor = 1 );
	// Scrolls the contents of the display to the right
	virtual void scrollRight( bool cursor = 1 );
	// Scrolls the contents of the display to the up
	virtual void scrollUp( bool cursor = 1 );
	// Scrolls the contents of the display to the down
	virtual void scrollDown( bool cursor = 1 );

	// Scrolls a line to the left
	virtual void scrollLeftLine( uint8_t line, bool cursor = 1 );
	// Scrolls a line to the right
	virtual void scrollRightLine( uint8_t line, bool cursor = 1 );

	// Defines a custom character
	virtual void defChar( uint8_t index, const uint8_t *data );
	// Sets the cursor mode
	virtual void setCursor( uint8_t mode );
	// Sets the autoscroll mode
	virtual void setAutoscroll( uint8_t mode );

protected:

	// Output interfaces to the display
	iface::output *m_mode;
	iface::output *m_data;

	// Size of the display
	uint8_t m_cols, m_rows;

	// Number of characters
	size_t m_size;

	// Font height
	uint8_t m_font_height;

	// Text buffer
	uint8_t *m_buffer;

	// Cursor position
	uint8_t m_pos[2];

	// Autoscroll mode
	uint8_t m_autoscroll;

	// Toggles the enable pin
	void strobe();

	// Sends nibble data to the display
	virtual void send( uint8_t data, size_t wait = 0 );

	// Sends data to the display
	virtual void sendSerial( uint8_t data, size_t wait = 0 );

	// Checks if the current line is full
	virtual bool isLineFull();
};

} // End of displays namespace

} // End of main namespace

#endif
