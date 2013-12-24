/* 
    Title --- display/hd44780-inl.hpp

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


#ifndef _RPI_HW_DISPLAY_HD44780_INL_HPP_
#define _RPI_HW_DISPLAY_HD44780_INL_HPP_

namespace rpihw { // Begin main namespace

namespace display { // Begin displays namespace

inline void
hd44780::cmd( uint8_t data ) {

	// Set RS value to low
	m_mode->write( 0, 0 );

	// Send the command to the display
	sendSerial( data, 5000 );
}

inline uint8_t
hd44780::getCursorX() const {

	// Return cursor x position
	return m_pos_x;
}

inline uint8_t
hd44780::getCursorY() const {

	// Return cursor x position
	return m_pos_y;
}

inline uint8_t
hd44780::getChar( uint8_t x, uint8_t y ) const {

	// Return a character from the buffer
	return m_buffer[ x + y * m_width ];
}

inline void
hd44780::write( uint8_t x, uint8_t y, uint8_t c ) {

	// Set the position of the cursor on the display
	move( x, y );

	// Write the character on the display
	write( c );
}

inline void
hd44780::write( const std::string &text, uint8_t flags ) {

	// Align the text and write it on the display
	write( utils::align( text, m_width, flags ) );
}

inline void
hd44780::write( uint8_t x, uint8_t y, const std::string &text ) {

	// Set the position of the cursor on the display
	move( x, y );

	// Write the string on the display
	write( text );
}

inline void
hd44780::write( uint8_t x, uint8_t y, const std::string &text, uint8_t flags ) {

	// Set the position of the cursor on the display
	move( x, y );

	// Write the string on the display
	write( text, flags );
}

inline void
hd44780::write( const std::u32string &text, uint8_t flags ) {

	// Align the text and write it on the display
	write( utils::align( text, m_width, flags ) );
}

inline void
hd44780::write( const std::wstring &text, uint8_t flags ) {

    // Align the text and write it on the display
    write( utils::align( text, m_width, flags ) );
}

inline void
hd44780::write( uint8_t x, uint8_t y, const std::u32string &text ) {

	// Set the position of the cursor on the display
	move( x, y );

	// Write the unicode string on the display
	write( text );
}

inline void
hd44780::write( uint8_t x, uint8_t y, const std::wstring &text ) {

    // Set the position of the cursor on the display
    move( x, y );

    // Write the unicode string on the display
    write( text );
}

inline void
hd44780::write( uint8_t x, uint8_t y, const std::u32string &text, uint8_t flags ) {

	// Set the position of the cursor on the display
	move( x, y );

	// Write the unicode string on the display
	write( text, flags );
}

inline void
hd44780::write( uint8_t x, uint8_t y, const std::wstring &text, uint8_t flags ) {

    // Set the position of the cursor on the display
    move( x, y );

    // Write the unicode string on the display
    write( text, flags );
}

inline void
hd44780::setTypingDelay( size_t delay ) {

	// Set the typing delay
	m_typing_delay = delay;
}

inline size_t
hd44780::getTypingDelay() const {

	// Return the typing delay
	return m_typing_delay;
}

inline void
hd44780::setAutoscroll( uint8_t mode ) {

	// Set the autoscroll mode
	m_autoscroll = mode;
}

} // End of displays namespace

} // End of main namespace

#endif /* _RPI_HW_DISPLAY_HD44780_INL_HPP_ */
