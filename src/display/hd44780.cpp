/* 
    Title --- display/hd44780.cpp

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


#ifndef _RPI_HW_DISPLAY_HD44780_CPP_
#define _RPI_HW_DISPLAY_HD44780_CPP_

#include <rpi-hw/display/hd44780.hpp>

namespace rpihw { // Begin main namespace

namespace display { // Begin displays namespace

hd44780::hd44780( uint8_t rs, uint8_t e, __ENUM_PARAMS( uint8_t, d, 4, 7 ) )

	: m_mode( new iface::output( { rs, e } ) )
	, m_data( new iface::output( { __ENUM( d, 4, 7 ) } ) ) {

}

hd44780::hd44780( uint8_t rs, uint8_t e, __ENUM_PARAMS( uint8_t, d, 0, 7 ) )

	: m_mode( new iface::output( { rs, e } ) )
	, m_data( new iface::output( { __ENUM( d, 0, 7 ) } ) ) {

}

hd44780::~hd44780() {

	// Destroy the interfaces
	delete m_mode;
	delete m_data;
}

void
hd44780::init( uint8_t cols, uint8_t rows, RomCodes rom_code, bool font ) {

	// Store the size of the display
	m_width		= cols;
	m_height	= math::min< uint8_t >( rows, 4 );

	// Create a new character buffer
	m_buffer.assign( m_width * m_height, ' ' );

	// Store the ROM code
	m_rom_code = rom_code;

	// Store the font size
	m_font_height = font ? 10 : 8;

	// Set the address locations
	// see: http://web.alfredstate.edu/weimandn/lcd/lcd_addressing/lcd_addressing_index.html
	m_lines[0] = 0x00;
	m_lines[1] = 0x40;

	if ( m_height == 4 && m_width == 16 ) {

		m_lines[2] = 0x10;
		m_lines[3] = 0x50;

	} else {

		m_lines[2] = 0x14;
		m_lines[3] = 0x54;
	}


	// Wait 20ms for LCD to power up
	time::msleep( 20 );

	// Initialize the display
	uint8_t flags = FUNC | FUNC_DL;

	// If required, enable the 4-bit mode
	if ( m_data->size() == 4 ) {

		flags >>= 4;

		sendData( flags, 5000 );
		sendData( flags, 200 );
		sendData( flags, 200 );

		flags = FUNC;
		sendData( flags >> 4, 5000 );

	} else {

		sendData( flags, 5000 );
		sendData( flags, 200 );
		sendData( flags, 200 );
	}

	// Apply settings
	if ( m_height > 1 )			flags |= FUNC_N;
	if ( m_font_height == 10 )	flags |= FUNC_F; 

	cmd( flags );
	cmd( POWER | POWER_D );
	cmd( ENTRY | ENTRY_ID );
	cmd( CLEAR );

	// Set the initial cursor position
	move( 0, 0 );
}

void
hd44780::strobe() {

	// Toggle the enable pin
	m_mode->write( 1, 1 );
	time::usleep( 50 );
	m_mode->write( 1, 0 );
}

void
hd44780::sendData( uint8_t data, size_t delay ) {

	// Send the nibble to the display
	m_data->write( data );

	// Toggle the enable pin
	strobe();

	// Wait some time
	time::usleep( delay );
}

void
hd44780::sendSerial( uint8_t data, size_t delay ) {

	// If the display uses 4-bit mode send the high nibble
	if ( m_data->size() == 4 )
		sendData( data >> 4, delay );

	// Send rest of data to the display
	sendData( data, delay );
}

void
hd44780::home() {

	// Home the cursor
	cmd( HOME );

	// Reset the cursor position
	m_pos_x = m_pos_y = 0;
}

void
hd44780::move( uint8_t x, uint8_t y ) {

	// Check if position exists
	if ( x >= m_width || y >= m_height )
		throw exception( utils::format( "(Fatal) `hd44780::move`: the position (%u,%u) does not exists\n", x, y ) );

	// Update the cursor position
	m_pos_x = x;
	m_pos_y = y;

	// Set the position of the cursor on the display
	cmd( DDRAM | ( m_lines[y] + x ) );
}

void
hd44780::putChar( uint8_t c ) {

	// Set RS value to high
	m_mode->write( 0, 1 );

	// Send the character to the display
	sendSerial( c, 200 );

	// Copy the character into the buffer
	m_buffer[ m_pos_x + m_pos_y * m_width ] = c;

	// Increment the x-position of the cursor 
	++m_pos_x;
}

void
hd44780::newLine() {

	// If there are still lines available move the cursor to the next line 
	if ( m_pos_y < m_height - 1 ) move( 0, m_pos_y + 1 );

	// Else move the cursor to the first column and scroll up the contents
	else if ( m_autoscroll & VSCROLL ) {

		move( 0, m_pos_y );
		scrollUp( false );

	// Else clear the display
	} else clear();
}

void
hd44780::write( uint8_t c ) {

	// Parse the character
	switch ( c ) {

		// Carriage-return character
		case '\r': { move( 0, m_pos_y ); break; }

		// New-line character
		case '\n': { newLine(); break; }

		// Normal character
		default: {

			// Check if there are no places available in the line
			if ( m_pos_x == m_width ) {

				// Make room for the new character
				if ( m_autoscroll & HSCROLL )
					scrollLeft();

				else if ( m_autoscroll & HSCROLL_LINE )
					scrollLeftLine( m_pos_y );

				else newLine();
			}

			// Put the character on the display
			putChar( c );

			// Wait some time (corresponding to the typing delay)
			if ( m_typing_delay && !std::isspace( c ) )
				time::msleep( m_typing_delay );

			break;
		}
	}
}

void
hd44780::write( const std::string &text ) {

	// Write the string on the display
	for ( auto &c : text ) {

		// Put the character on the display
		write( (uint8_t) c );
	}
}

void
hd44780::write( const std::u32string &text ) {

	// Write the string on the display
	for ( auto &c : text ) {

		// Encode the character and put it on the display
		switch ( m_rom_code ) {

			case ROM_A00: { write( encode_char_a00( c ) ); break; }
			case ROM_A02: { write( encode_char_a02( c ) ); break; }

			default: { write( encode_char_a00( c ) ); break; }
		}
	}
}

void
hd44780::scrollLeft( bool cursor ) {

	// Hardware: cmd( SHIFT | SHIFT_SC );

	// Store the cursor position
	uint8_t x = m_pos_x - (uint8_t) cursor,
			y = m_pos_y;

	// Iterators
	uint8_t i, j;

	// Move left the contents
	for ( j = 0; j < m_height; ++j ) {

		move( 0, j );

		for ( i = 0; i < m_width - 1; ++i )
			putChar( getChar( i + 1, j ) );
	}

	// Clear the last column
	for ( i = m_width - 1, j = 0; j < m_height; ++j ) {

		move( i, j ); putChar( ' ' );
	}

	// Restore the cursor position
	move( x, y );
}

void
hd44780::scrollRight( bool cursor ) {

	// Hardware: cmd( SHIFT | SHIFT_SC | SHIFT_R );

	// Store the cursor position
	uint8_t x = m_pos_x + (uint8_t) cursor,
			y = m_pos_y;

	// Iterators
	uint8_t i, j;

	// Move right the contents
	for ( j = 0; j < m_height; ++j ) {

		for ( i = m_width - 1; i >= 1; --i )
			m_buffer[ i + j * m_width ] = getChar( i - 1, j );

		move( 1, j );

		for ( i = 1; i < m_width; ++i )
			putChar( getChar( i, j ) );
	}

	// Clear the first column
	for ( i = 0, j = 0; j < m_height; ++j ){

		move( i, j ); putChar( ' ' );
	}

	// Restore the cursor position
	move( x, y );
}

void
hd44780::scrollUp( bool cursor ) {

	// Store the cursor position
	uint8_t x = m_pos_x,
			y = m_pos_y - (uint8_t) cursor;

	// Iterators
	uint8_t i, j;

	// Move up the contents
	for ( j = 0; j < m_height - 1; ++j ) {

		move( 0, j );

		for ( i = 0; i < m_width; ++i )
			putChar( getChar( i, j + 1 ) );
	}

	// Clear the last row
	move( 0, m_height - 1 );

	for ( i = 0; i < m_width; ++i )
		putChar( ' ' );

	// Restore the cursor position
	move( x, y );
}

void
hd44780::scrollDown( bool cursor ) {

	// Store the cursor position
	uint8_t x = m_pos_x,
			y = m_pos_y + (uint8_t) cursor;

	// Iterators
	uint8_t i, j;

	// Move down the contents
	for ( j = m_height - 1; j >= 1; --j ) {

		move( 0, j );

		for ( i = 0; i < m_width; ++i )
			putChar( getChar( i, j - 1 ) );
	}

	// Clear the first row
	move( 0, 0 );

	for ( i = 0; i < m_width; ++i )
		putChar( ' ' );

	// Restore the cursor position
	move( x, y );
}

void
hd44780::scrollLeftLine( uint8_t line, bool cursor ) {

	// Store the cursor position
	uint8_t x = m_pos_x - (uint8_t) cursor,
			y = m_pos_y;

	// Iterator
	uint8_t i;

	// Scroll the line to the left
	move( 0, line );

	for ( i = 0; i < m_width - 1; ++i )
		putChar( getChar( i + 1, line ) );

	putChar( ' ' );

	// Restore the cursor position
	move( x, y );
}

void
hd44780::scrollRightLine( uint8_t line, bool cursor ) {

	// Store the cursor position
	uint8_t x = m_pos_x + (uint8_t) cursor,
			y = m_pos_y;

	// Iterator
	uint8_t i;

	// Scroll the line to the right
	for ( i = m_width - 1; i >= 1; --i )
		m_buffer[ i + line * m_width ] = getChar( i - 1, line );

	move( 0, line ); putChar( ' ' );

	for ( i = 1; i < m_width; ++i )
		putChar( getChar( i, line ) );

	// Restore the cursor position
	move( x, y );
}

void
hd44780::defChar( uint8_t index, const uint8_t *data ) {

	// Check if custom character is valid
	if ( index > 7 )
		throw exception( "(Fatal) `hd44780::defChar`: could not define new custom character, index out of range\n" );

	// Start definition of the custom character
	cmd( CGRAM | ( index * 8 ) );

	// Set RS value to high
	m_mode->write( 0, 1 );

	// Iterator
	uint8_t i = 0;

	// Define the custom character
	for ( ; i < m_font_height; ++i )
		sendSerial( data[i], 5000 );

	// Restore the cursor position
	move( m_pos_x, m_pos_y );
}

void
hd44780::setCursor( uint8_t mode ) {

	// Set the cursor mode
	uint8_t flags = POWER | POWER_D;

	if ( mode & CURSOR_SOLID )		flags |= POWER_C; 
	if ( mode & CURSOR_BLINKING )	flags |= POWER_B; 

	cmd( flags );
}

void
hd44780::clear() {

	// Clear the display
	cmd( CLEAR );

	// Reset the cursor position
	m_pos_x = m_pos_y = 0;

	// Clear the character buffer
	m_buffer.assign( m_buffer.size(), ' ' );
}

uint8_t
hd44780::encode_char_a00( char32_t code ) {

	// Standard ASCII characters
	if ( code <= 0x7d && code != 0x5c )
		return (uint8_t) code;

	// Parse all supported characters
	switch ( code ) {

		case 0x00a5: return 0x4c;	// Yen sign
		case 0x2192: return 0x7e;	// Rightwards arrow
		case 0x2190: return 0x7f;	// Leftwards arrow
		case 0x3002: return 0xa1;	// Ideographic full stop
		case 0x231c: return 0xa2;	// Top left corner
		case 0x231f: return 0xa3;	// Bottom right corner
		case 0x3001: return 0xa4;	// Ideographic comma
		case 0x30fb: return 0xa5;	// Katakana middle dot
		case 0x30f2: return 0xa6;	// Katakana letter wo
		case 0x30a1: return 0xa7;	// Katakana letter small a
		case 0x30a3: return 0xa8;	// Katakana letter small i
		case 0x30a5: return 0xa9;	// Katakana letter small u
		case 0x30a7: return 0xaa;	// Katakana letter small e
		case 0x30a9: return 0xab;	// Katakana letter small o
		case 0x30e3: return 0xac;	// Katakana letter small ya
		case 0x30e5: return 0xad;	// Katakana letter small yu
		case 0x30e7: return 0xae;	// Katakana letter small yo
		case 0x30c3: return 0xaf;	// Katakana letter small tu
		case 0x30fc: return 0xb0;	// Katakana-hiragana prolonged sound mark
		case 0x30a2: return 0xb1;	// Katakana letter a
		case 0x30a4: return 0xb2;	// Katakana letter i
		case 0x30a6: return 0xb3;	// Katakana letter u
		case 0x30a8: return 0xb4;	// Katakana letter e
		case 0x30aa: return 0xb5;	// Katakana letter o
		case 0x30ab: return 0xb6;	// Katakana letter ka
		case 0x30ad: return 0xb7;	// Katakana letter ki
		case 0x30af: return 0xb8;	// Katakana letter ku
		case 0x30b1: return 0xb9;	// Katakana letter ke
		case 0x30b3: return 0xba;	// Katakana letter ko
		case 0x30b5: return 0xbb;	// Katakana letter sa
		case 0x30b7: return 0xbc;	// Katakana letter si
		case 0x30b9: return 0xbd;	// Katakana letter su
		case 0x30bb: return 0xbe;	// Katakana letter se
		case 0x30bd: return 0xbf;	// Katakana letter so
		case 0x30bf: return 0xc0;	// Katakana letter ta
		case 0x30c1: return 0xc1;	// Katakana letter ti
		case 0x30c4: return 0xc2;	// Katakana letter tu
		case 0x30c6: return 0xc3;	// Katakana letter te
		case 0x30c8: return 0xc4;	// Katakana letter to
		case 0x30ca: return 0xc5;	// Katakana letter na
		case 0x30cb: return 0xc6;	// Katakana letter ni
		case 0x30cc: return 0xc7;	// Katakana letter nu
		case 0x30cd: return 0xc8;	// Katakana letter ne
		case 0x30ce: return 0xc9;	// Katakana letter no
		case 0x30cf: return 0xca;	// Katakana letter ha
		case 0x30d2: return 0xcb;	// Katakana letter hi
		case 0x30d5: return 0xcc;	// Katakana letter hu
		case 0x30d8: return 0xcd;	// Katakana letter he
		case 0x30db: return 0xce;	// Katakana letter ho
		case 0x30de: return 0xcf;	// Katakana letter ma
		case 0x30df: return 0xd0;	// Katakana letter mi
		case 0x30e0: return 0xd1;	// Katakana letter mu
		case 0x30e1: return 0xd2;	// Katakana letter me
		case 0x30e2: return 0xd3;	// Katakana letter mo
		case 0x30e4: return 0xd4;	// Katakana letter ya
		case 0x30e6: return 0xd5;	// Katakana letter yu
		case 0x30e8: return 0xd6;	// Katakana letter yo
		case 0x30e9: return 0xd7;	// Katakana letter ra
		case 0x30ea: return 0xd8;	// Katakana letter ri
		case 0x30eb: return 0xd9;	// Katakana letter ru
		case 0x30ec: return 0xda;	// Katakana letter re
		case 0x30ed: return 0xdb;	// Katakana letter ro
		case 0x30ef: return 0xdc;	// Katakana letter wa
		case 0x30f3: return 0xdd;	// Katakana letter n
		case 0x309b: return 0xde;	// Katakana-hiragana voiced sound mark
		case 0x309c: return 0xdf;	// Katakana-hiragana semi-voiced sound mark
		case 0x03b1: return 0xe0;	// Greek small letter alpha
		case 0x00e4: return 0xe1;	// Latin small letter a with diaeresis
		case 0x03b2: return 0xe2;	// Greek small letter beta
		case 0x03b5: return 0xe3;	// Greek small letter epsilon
		case 0x03bc: return 0xe4;	// Greek small letter mu
		case 0x03c3: return 0xe5;	// Greek small letter sigma
		case 0x03c1: return 0xe6;	// Greek small letter rho
		/* 0xe7 */
		case 0x221a: return 0xe8;	// Square root
		/* 0xe9 */
		/* 0xea */
		case 0x02df: return 0xeb;	// Modifier letter cross accent
		case 0xffe0: return 0xec;	// Fullwidth cent sign
		case 0x2c60: return 0xed;	// Latin capital letter l with double bar
		case 0x00f1: return 0xee;	// Latin small letter n with tilde
		case 0x00f6: return 0xef;	// Latin small letter o with diaeresis
		/* 0xf0 */
		/* 0xf1 */
		case 0x0398: return 0xf2;	// Greek capital letter theta
		case 0x221E: return 0xf3;	// Infinity
		case 0x03a9: return 0xf4;	// Greek capital letter omega
		case 0x00fc: return 0xf5;	// Latin small letter u with diaeresis
		case 0x03a3: return 0xf6;	// Greek capital letter sigma
		case 0x03c0: return 0xf7;	// Greek small letter pi
		/* 0xf8 */
		/* 0xf9 */
		case 0x5343: return 0xfa;	// Cjk unified ideograph
		case 0x4e07: return 0xfb;	// Cjk unified ideograph
		case 0x5186: return 0xfc;	// Cjk unified ideograph
		case 0x00f7: return 0xfd;	// Division sign
		/* 0xfe */
		case 0x25a0: return 0xff;	// Black square

		default: return 0x20;
	}
}

uint8_t
hd44780::encode_char_a02( char32_t code ) {

	// Standard ASCII characters
	if	(
			code <= 0xff &&
			(
				( code <= 0x7e ) ||
				( code >= 0xa1 && code <= 0xa7 ) ||
				( code >= 0xa9 && code <= 0xab ) ||
				( code == 0xae ) ||
				( code >= 0xb1 && code <= 0xb3 ) ||
				( code >= 0xb5 && code <= 0xb7 ) ||
				( code >= 0xb9 && code <= 0xd7 ) ||
				( code >= 0xd9 && code <= 0xf7 ) ||
				( code >= 0xf9 && code <= 0xff )
			)

		) {

		return (uint8_t) code;
	}

	// Parse all supported characters
	switch ( code ) {

		case 0x25b6: return 0x10;	// Black right-pointing triangle
		case 0x25c0: return 0x11;	// Black left-pointing triangle
		case 0x201c: return 0x12;	// Left double quotation mark
		case 0x201d: return 0x13;	// Right double quotation mark
		case 0x25cf: return 0x16;	// Black circle
		case 0x21b5: return 0x17;	// Downwards arrow with corner leftwards
		case 0x2191: return 0x18;	// Upwards arrow
		case 0x2193: return 0x19;	// Downwards arrow
		case 0x2192: return 0x1a;	// Rightwards arrow
		case 0x2190: return 0x1b;	// Leftwards arrow
		case 0x2264: return 0x1c;	// Less-than or equal to
		case 0x2265: return 0x1d;	// Greater-than or equal to
		case 0x25b2: return 0x1e;	// Black up-pointing triangle
		case 0x25bc: return 0x1f;	// Black down-pointing triangle
		case 0x2302: return 0x7f;	// House
		case 0x0411: return 0x80;	// Cyrillic capital letter be
		case 0x0414: return 0x81;	// Cyrillic capital letter de
		case 0x0416: return 0x82;	// Cyrillic capital letter zhe
		case 0x0417: return 0x83;	// Cyrillic capital letter ze
		case 0x0418: return 0x84;	// Cyrillic capital letter i
		case 0x0419: return 0x85;	// Cyrillic capital letter short i
		case 0x041b: return 0x86;	// Cyrillic capital letter el
		case 0x041f: return 0x87;	// Cyrillic capital letter pe
		case 0x0423: return 0x88;	// Cyrillic capital letter u
		case 0x0426: return 0x89;	// Cyrillic capital letter tse
		case 0x0427: return 0x8a;	// Cyrillic capital letter che
		case 0x0428: return 0x8b;	// Cyrillic capital letter sha
		case 0x0429: return 0x8c;	// Cyrillic capital letter shcha
		case 0x042a: return 0x8d;	// Cyrillic capital letter hard sign
		case 0x042b: return 0x8e;	// Cyrillic capital letter yeru
		case 0x042D: return 0x8f;	// Cyrillic capital letter e
		case 0x03b1: return 0x90;	// Greek small letter alpha
		case 0x266a: return 0x91;	// Eighth note
		case 0x0393: return 0x92;	// Greek capital letter gamma
		case 0x03c0: return 0x93;	// Greek small letter pi
		case 0x03a3: return 0x94;	// Greek capital letter sigma
		case 0x03c3: return 0x95;	// Greek small letter sigma
		case 0x266c: return 0x96;	// Beamed sixteenth notes
		case 0x03c4: return 0x97;	// Greek small letter tau
		/* 0x98 */
		case 0x0398: return 0x99;	// Greek capital letter theta
		case 0x03a9: return 0x9a;	// Greek capital letter omega
		case 0x03b4: return 0x9b;	// Greek small letter delta
		case 0x221e: return 0x9c;	// Infinity
		case 0x2665: return 0x9d;	// Black heart suit
		case 0x03b5: return 0x9e;	// Greek small letter epsilon
		case 0x2229: return 0x9f;	// Intersection
		/* 0xa0 */
		case 0x0192: return 0xa8;	// Latin small letter f with hook
		case 0x042e: return 0xac;	// Cyrillic capital letter yu
		case 0x042f: return 0xad;	// Cyrillic capital letter ya
		case 0x2018: return 0xaf;	// Left single quotation mark
		case 0x2070: return 0xb0;	// Superscript zero
		case 0x20a7: return 0xb4;	// Peseta sign
		case 0x03c9: return 0xb8;	// Greek small letter omega
		case 0x03a6: return 0xd8;	// Greek capital letter phi
		case 0x03c6: return 0xf8;	// Greek small letter phi

		default: return 0x20;
	}
}

} // End of displays namespace

} // End of main namespace

#endif /* _RPI_HW_DISPLAY_HD44780_CPP_ */
