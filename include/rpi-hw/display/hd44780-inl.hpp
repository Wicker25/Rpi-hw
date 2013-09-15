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
hd44780::getChar( uint8_t x, uint8_t y ) const {

	// Return a character from the buffer
	return m_buffer[ x + y * m_screen_w ];
}

inline uint8_t
hd44780::getXCursor() const{
	
	//Return cursor x position
	return m_pos_x;
}

inline uint8_t
hd44780::getYCursor() const{
	
	//Return cursor x position
	return m_pos_y;
}

inline bool
hd44780::isLineFull() {

	// Check if the current line is full
	return ( m_pos_x >= m_screen_w );
}

inline void
hd44780::write( uint8_t x, uint8_t y, uint8_t chr ) {

	// Set the position of the cursor on the display
	move( x, y );

	// Write the character on the display
	write( chr );
}

inline void
hd44780::write( uint8_t x, uint8_t y, const std::string &text, size_t delay ) {

	// Set the position of the cursor on the display
	move( x, y );

	// Write the string on the display
	write( text, delay );
}

inline void
hd44780::setAutoscroll( uint8_t mode ) {

	// Set the autoscroll mode
	m_autoscroll = mode;
}

} // End of displays namespace

} // End of main namespace

#endif /* _RPI_HW_DISPLAY_HD44780_INL_HPP_ */
