/* 
    Title --- lcd20x4demo.cpp [examples]

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


#include <iostream>
#include <cstdio>

#include <rpi-hw.hpp>

#include <rpi-hw/utils.hpp>
#include <rpi-hw/utils-inl.hpp>

#include <rpi-hw/display/hd44780.hpp>
#include <rpi-hw/display/hd44780-inl.hpp>

// Use some namespaces
using namespace rpihw;
using namespace rpihw::display;

std::string exec( const std::string &cmd ) {

	// Open the process for reading
	FILE *pfile = popen( cmd.c_str(), "r" );

	if ( !pfile ) return "<failed>";

	// Output of the process and buffer
	std::string output;
	char buffer[128];

	// Copy the output of the process
	while ( !feof( pfile ) ) {

		if ( fgets( buffer, 128, pfile ) != NULL )
			output.append( buffer );
	}

	// Close the process
	pclose( pfile );

	return output;
}

void pause( hd44780 &disp, size_t seconds ) {

	// Wait some time and clear the display
	utils::sleep( seconds );
	disp.clear();
}

void demo0( hd44780 &disp ) {

	// Write the title
	disp.write( 4, 1, "= Demo #0 =" );
	disp.write( 4, 2, "Cursor mode" );
	pause( disp, 2 );

	// Write a text using the solid cursor
	disp.setCursor( hd44780::CURSOR_SOLID );
	disp.write( "Solid cursor", 200 );
	utils::sleep( 1 );

	// Write a text using the blinking cursor
	disp.setCursor( hd44780::CURSOR_BLINKING );
	disp.write( "\nBlinking cursor", 200 );
	utils::sleep( 1 );

	// Write a text using the both cursors 
	disp.setCursor( hd44780::CURSOR_SOLID | hd44780::CURSOR_BLINKING );
	disp.write( "\nBoth cursors", 200 );
	utils::sleep( 1 );

	// Hide cursor
	disp.setCursor( hd44780::NO_CURSOR );
	disp.write( "\nNo cursor", 200 );
	pause( disp, 2 );
}

void demo1( hd44780 &disp ) {

	// Write the title
	disp.write( 4, 1, "= Demo #1 =" );
	disp.write( 2, 2, "Move the cursor" );
	pause( disp, 2 );

	// Set solid cursor
	disp.setCursor( hd44780::CURSOR_SOLID );

	// Iterator
	uint8_t i = 0;

	// Move the cursor on the display
	for ( ; i < 20; i++ ) {

		disp.move( i, ( i % 4 ) );
		utils::msleep( 500 );
	}

	// Hide the cursor
	disp.setCursor( hd44780::NO_CURSOR );

	// Wait some time and clear the screen
	utils::sleep( 2 );
	disp.clear();
}

void demo2( hd44780 &disp ) {

	// Write the title
	disp.write( 4, 1, "= Demo #2 =" );
	disp.write( 2, 2, "Speed of writing" );
	pause( disp, 2 );

	// Write text at different speeds
	disp.write( "Slow speed", 500 );
	disp.write( "\nNormal speed", 200 );
	disp.write( "\nFast speed" );
	pause( disp, 2 );
}

void demo3( hd44780 &disp ) {

	// Write the title
	disp.write( 4, 1, "= Demo #3 =" );
	disp.write( 3, 2, "Text alignment" );
	pause( disp, 2 );

	// Write a text using the left alignment
	disp.write( 0, 1, "Left\nalignment", 0 );
	pause( disp, 2 );

	// Write a text using the center alignment
	disp.write( 0, 1, utils::align( "Center\nalignment", 20, utils::ALIGN_CENTER ), 0 );
	pause( disp, 2 );

	// Write a text using the right alignment
	disp.write( 0, 1, utils::align( "Right\nalignment", 20, utils::ALIGN_RIGHT ), 0 );
	pause( disp, 2 );
}

void demo4( hd44780 &disp ) {

	// Write the title
	disp.write( 4, 1, "= Demo #4 =" );
	disp.write( 0, 2, "Scroll the contents" );
	utils::sleep( 2 );
	disp.clear();

	// Write a sample text
	disp.write( "Vertical scrolling" );
	utils::sleep( 2 );

	// Scroll down the screen
	disp.scrollDown(); utils::msleep( 500 );
	disp.scrollDown(); utils::msleep( 500 );
	disp.scrollDown(); utils::msleep( 500 );

	// Scroll up the screen
	disp.scrollUp(); utils::msleep( 500 );
	disp.scrollUp(); utils::msleep( 500 );
	disp.scrollUp();

	// Wait some time and clear the screen
	pause( disp, 2 );

	// Write a sample text
	disp.write( 0, 1, "Horizontal\nscrolling" );
	utils::sleep( 1 );

	// Scroll right the screen
	disp.scrollRight(); utils::msleep( 500 );
	disp.scrollRight(); utils::msleep( 500 );
	disp.scrollRight(); utils::msleep( 500 );
	disp.scrollRight(); utils::msleep( 500 );

	// Scroll left the screen
	disp.scrollLeft(); utils::msleep( 500 );
	disp.scrollLeft(); utils::msleep( 500 );
	disp.scrollLeft(); utils::msleep( 500 );
	disp.scrollLeft();

	// Wait some time and clear the screen
	pause( disp, 2 );
}

void demo5( hd44780 &disp ) {

	// Write the title
	disp.write( 4, 1, "= Demo #5 =" );
	disp.write( 3, 2, "Autoscrolling" );
	pause( disp, 2 );

	// A sample text
	std::string text =	"First line.\n"
						"Second line.\n"
						"Third looooooooooooong line!\n"
						"Fourth line.\n"
						"Fifth line.\n"
						"Sixth line.";

	// Write the text without scrolling
	disp.write( 3, 1, "No scrolling" );
	pause( disp, 2 );

	disp.setAutoscroll( hd44780::NO_SCROLL );
	disp.write( text, 150 );
	pause( disp, 1 );

	// Write the text with vertical autoscrolling
	disp.write( 6, 1, "Vertical" );
	pause( disp, 2 );

	disp.setAutoscroll( hd44780::VSCROLL );
	disp.write( text, 150 );
	pause( disp, 1 );

	// Write the text with horizontal autoscrolling
	disp.write( 5, 1, "Horizontal" );
	pause( disp, 2 );

	disp.setAutoscroll( hd44780::HSCROLL );
	disp.write( text, 150 );
	pause( disp, 2 );

	// Write the text with horizontal autoscrolling (single line)
	disp.write( 1, 1, "Horizontal (line)" );
	pause( disp, 2 );

	disp.setAutoscroll( hd44780::HSCROLL_LINE );
	disp.write( text, 150 );
	pause( disp, 2 );

	// Write the text with horizontal (single line) and vertical autoscrolling
	disp.write( 0, 1, utils::align( "Horizontal (line) and vertical", 20, utils::ALIGN_CENTER ) );
	pause( disp, 2 );

	disp.setAutoscroll( hd44780::HSCROLL_LINE | hd44780::VSCROLL );
	disp.write( text, 150 );

	// Restore the autoscrolling
	disp.setAutoscroll( hd44780::VSCROLL );

	// Wait some time and clear the screen
	pause( disp, 2 );
}

void demo6( hd44780 &disp ) {

	// Write the title
	disp.write( 4, 1, "= Demo #6 =" );
	disp.write( 3, 2, "Word wrapping" );
	pause( disp, 2 );

	// A sample text
	std::string text =	"To be, or not to be, that is the question: "
						"whether 'tis nobler in the mind to suffer "
						"the slings and arrows of outrageous fortune, "
						"or to take arms against a sea of troubles, "
						"and, by opposing, end them. To die, to sleep...";

	// Write the text with word wrapping
	disp.write( utils::align( text, 20, utils::ALIGN_CENTER ), 200 );
	pause( disp, 2 );
}

void demo7( hd44780 &disp ) {

	// Write the title
	disp.write( 4, 1, "= Demo #7 =" );
	disp.write( 1, 2, "Custom characters" );
	pause( disp, 2 );

	// Display loading message
	disp.write( 5, 1, "Loading..." );

	// Define some custom characters
	uint8_t smile[8]		= { 0x00, 0x0a, 0x0a, 0x00, 0x00, 0x11, 0x0e, 0x00 };
	uint8_t heart[8]		= { 0x00, 0x0a, 0x1f, 0x1f, 0x1f, 0x0e, 0x04, 0x00 };
	uint8_t pacman[8]		= { 0x0e, 0x1d, 0x1f, 0x1c, 0x18, 0x1c, 0x1f, 0x0e };
	uint8_t music[8]		= { 0x03, 0x0d, 0x09, 0x09, 0x09, 0x0b, 0x1b, 0x18 };

	uint8_t bat_left[8]		= { 0x02, 0x06, 0x0f, 0x0f, 0x0f, 0x0f, 0x06, 0x02 };
	uint8_t bat_center[8]	= { 0x0a, 0x0e, 0x1f, 0x1f, 0x1f, 0x1f, 0x0e, 0x04 };
	uint8_t bat_right[8]	= { 0x08, 0x0c, 0x1e, 0x1e, 0x1e, 0x1e, 0x0c, 0x08 };

	disp.defChar( hd44780::CCHAR0, smile );
	disp.defChar( hd44780::CCHAR1, heart );
	disp.defChar( hd44780::CCHAR2, pacman );
	disp.defChar( hd44780::CCHAR3, music );

	disp.defChar( hd44780::CCHAR4, bat_left );
	disp.defChar( hd44780::CCHAR5, bat_center );
	disp.defChar( hd44780::CCHAR6, bat_right );

	// Clear the display
	disp.clear();

	// Write the custom characters
	disp.write( 1, 0, "Smile  " );
	disp.write( hd44780::CCHAR0 );

	disp.write( 12, 0, hd44780::CCHAR1 );
	disp.write( " Heart" );

	disp.write( 1, 1, "Pacman " );
	disp.write( hd44780::CCHAR2 );

	disp.write( 12, 1, hd44780::CCHAR3 );
	disp.write( " Music" );

	disp.write( 4, 3, "Batman! " );
	disp.write( hd44780::CCHAR4 );
	disp.write( hd44780::CCHAR5 );
	disp.write( hd44780::CCHAR6 );

	// Wait some time and clear the screen
	pause( disp, 6 );
}

void demo8( hd44780 &disp ) {

	// Write the title
	disp.write( 4, 1, "= Demo #8 =" );
	disp.write( 1, 2, "Print current time" );
	pause( disp, 2 );

	// Write the current date
	size_t i = 0;

	for ( ; i < 10; i++ ) {

		disp.write( 0, 1, utils::align( exec( "date +%H:%m:%S" ), 20, utils::ALIGN_CENTER ) );
		pause( disp, 1 );
	}

	// Wait some time and clear the screen
	pause( disp, 1 );
}

void demo9( hd44780 &disp ) {

	// Write the title
	disp.write( 4, 1, "= Demo #9 =" );
	disp.write( 3, 2, "Progress bars" );
	pause( disp, 2 );

	// Draw the progress bars
	float factor = 100.0 / 18.0;

	size_t i = 0;

	for ( ; i <= 100; i += 5 ) {

		disp.write( 0, 1, utils::align( utils::format( "%zu%%", i ), 20, utils::ALIGN_CENTER ) );
		disp.write( 1, 2, std::string( (size_t) math::abs( (float) i / factor ), 0xFF ) );

		utils::msleep( 500 );
	}

	pause( disp, 2 );

	for ( i = 0; i <= 100; i += 5 ) {

		disp.write( 0, 1, utils::align( utils::format( "%zu%%", i ), 20, utils::ALIGN_CENTER ) );
		disp.write( 0, 2, "[" + std::string( (size_t) math::abs( (float) i / factor ), '=' ) );
		disp.write( 19, 2, "]" );
	
		utils::msleep( 500 );
	}

	// Wait some time and clear the screen
	pause( disp, 2 );
}

void demo10( hd44780 &disp ) {

	// Write the title
	disp.write( 3, 1, "= Demo #10 =" );
	disp.write( 1, 2, "Directory contents" );
	pause( disp, 2 );

	// Write the contents of the directory
	disp.write( "Directory contents\n" );
	disp.write( exec( "ls | awk '{print FNR \" \" $0}'" ), 200 );
	pause( disp, 2 );
}

void demo11( hd44780 &disp ) {

	// Write the title
	disp.write( 3, 1, "= Demo #11 =" );
	disp.write( 1, 2, "Wireless networks" );
	pause( disp, 2 );

	// Write the list of the wireless networks
	disp.write( 0, 0, "Scanning..." );
	std::string list = exec( "iwlist wlan0 scanning | sed -n 's/.*ESSID:\"\\(.*\\)\"/\\1/p' | awk '{ print FNR, $0 }'" );
	disp.clear();

	disp.write( "Wireless networks\n" );
	disp.write( list, 200 );

	// Wait some time and clear the screen
	utils::sleep( 2 );
	disp.clear();
}

int
main( int argc, char *args[] ) {

	// Display controller
	hd44780 disp( 14, 18, 4, 17, 21, 22 );

	// Initialize the 16x2 display
	disp.init( 20, 4 );

	// Print the initial messages
	disp.write( utils::align(

		"= Rpi-hw =\n"
		"Interfacing Raspberry Pi with Hitachi HD44780",

	20, utils::ALIGN_CENTER ) );

	pause( disp, 5 );

	disp.write( utils::align(

		"Rpi-hw is a free C++ library designed to manage "
		"the Raspberry Pi's GPIO connector.",

	20, utils::ALIGN_CENTER ), 200 );

	pause( disp, 2 );

	// Play all demos
	demo0( disp );
	demo1( disp );
	demo2( disp );
	demo3( disp );
	demo4( disp );
	demo5( disp );
	demo6( disp );
	demo7( disp );
	demo8( disp );
	demo9( disp );
	demo10( disp );
	//demo11( disp );

	// Print the final message
	disp.write( utils::align( "That's all, folks!\nFeel free to comment my work!", 20, utils::ALIGN_CENTER ), 200 );
	pause( disp, 2 );
	disp.write( utils::align( "For more informations visit:\n\nwww.hackyourmind.org", 20, utils::ALIGN_CENTER ), 200 );
	pause( disp, 2 );

	/*
	disp.write( utils::align( "A special thanks to my friend Nicola for helping me with this video!", 20, utils::ALIGN_CENTER ), 200 );
	disp.write( hd44780::CCHAR0 );
	pause( disp, 2 );
	*/

	return 0;
}

