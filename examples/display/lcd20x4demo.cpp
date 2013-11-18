/* 
    Title --- lcd20x4demo.cpp [examples]

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


// Include Rpi-hw headers
#include <rpi-hw.hpp>
#include <rpi-hw/utils.hpp>
#include <rpi-hw/time.hpp>
#include <rpi-hw/display/hd44780.hpp>

// Use Rpi-hw namespaces
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

void pause( hd44780 &dev, size_t seconds ) {

	// Wait some time and clear the display
	time::sleep( seconds );
	dev.clear();
}

void demo0( hd44780 &dev ) {

	// Write the title
	dev.write( 4, 1, "= Demo #0 =" );
	dev.write( 4, 2, "Cursor mode" );
	pause( dev, 2 );

	// Write a text using the solid cursor
	dev.setCursor( hd44780::CURSOR_SOLID );
	dev.write( "Solid cursor", 200 );
	time::sleep( 1 );

	// Write a text using the blinking cursor
	dev.setCursor( hd44780::CURSOR_BLINKING );
	dev.write( "\nBlinking cursor", 200 );
	time::sleep( 1 );

	// Write a text using the both cursors 
	dev.setCursor( hd44780::CURSOR_SOLID | hd44780::CURSOR_BLINKING );
	dev.write( "\nBoth cursors", 200 );
	time::sleep( 1 );

	// Hide cursor
	dev.setCursor( hd44780::NO_CURSOR );
	dev.write( "\nNo cursor", 200 );
	pause( dev, 2 );
}

void demo1( hd44780 &dev ) {

	// Write the title
	dev.write( 4, 1, "= Demo #1 =" );
	dev.write( 2, 2, "Move the cursor" );
	pause( dev, 2 );

	// Set solid cursor
	dev.setCursor( hd44780::CURSOR_SOLID );

	// Iterator
	uint8_t i = 0;

	// Move the cursor on the display
	for ( ; i < 20; ++i ) {

		dev.move( i, ( i % 4 ) );
		time::msleep( 500 );
	}

	// Hide the cursor
	dev.setCursor( hd44780::NO_CURSOR );

	// Wait some time and clear the screen
	time::sleep( 2 );
	dev.clear();
}

void demo2( hd44780 &dev ) {

	// Write the title
	dev.write( 4, 1, "= Demo #2 =" );
	dev.write( 2, 2, "Speed of writing" );
	pause( dev, 2 );

	// Write text at different speeds
	dev.write( "Slow speed", 500 );
	dev.write( "\nNormal speed", 200 );
	dev.write( "\nFast speed" );
	pause( dev, 2 );
}

void demo3( hd44780 &dev ) {

	// Write the title
	dev.write( 4, 1, "= Demo #3 =" );
	dev.write( 3, 2, "Text alignment" );
	pause( dev, 2 );

	// Write a text using the left alignment
	dev.write( 0, 1, "Left\nalignment", 0 );
	pause( dev, 2 );

	// Write a text using the center alignment
	dev.write( 0, 1, utils::align( "Center\nalignment", 20, utils::ALIGN_CENTER ), 0 );
	pause( dev, 2 );

	// Write a text using the right alignment
	dev.write( 0, 1, utils::align( "Right\nalignment", 20, utils::ALIGN_RIGHT ), 0 );
	pause( dev, 2 );
}

void demo4( hd44780 &dev ) {

	// Write the title
	dev.write( 4, 1, "= Demo #4 =" );
	dev.write( 0, 2, "Scroll the contents" );
	time::sleep( 2 );
	dev.clear();

	// Write a sample text
	dev.write( "Vertical scrolling" );
	time::sleep( 2 );

	// Scroll down the screen
	dev.scrollDown(); time::msleep( 500 );
	dev.scrollDown(); time::msleep( 500 );
	dev.scrollDown(); time::msleep( 500 );

	// Scroll up the screen
	dev.scrollUp(); time::msleep( 500 );
	dev.scrollUp(); time::msleep( 500 );
	dev.scrollUp();

	// Wait some time and clear the screen
	pause( dev, 2 );

	// Write a sample text
	dev.write( 0, 1, "Horizontal\nscrolling" );
	time::sleep( 1 );

	// Scroll right the screen
	dev.scrollRight(); time::msleep( 500 );
	dev.scrollRight(); time::msleep( 500 );
	dev.scrollRight(); time::msleep( 500 );
	dev.scrollRight(); time::msleep( 500 );

	// Scroll left the screen
	dev.scrollLeft(); time::msleep( 500 );
	dev.scrollLeft(); time::msleep( 500 );
	dev.scrollLeft(); time::msleep( 500 );
	dev.scrollLeft();

	// Wait some time and clear the screen
	pause( dev, 2 );
}

void demo5( hd44780 &dev ) {

	// Write the title
	dev.write( 4, 1, "= Demo #5 =" );
	dev.write( 3, 2, "Autoscrolling" );
	pause( dev, 2 );

	// A sample text
	std::string text =	"First line.\n"
						"Second line.\n"
						"Third looooooooooooong line!\n"
						"Fourth line.\n"
						"Fifth line.\n"
						"Sixth line.";

	// Write the text without scrolling
	dev.write( 3, 1, "No scrolling" );
	pause( dev, 2 );

	dev.setAutoscroll( hd44780::NO_SCROLL );
	dev.write( text, 150 );
	pause( dev, 1 );

	// Write the text with vertical autoscrolling
	dev.write( 6, 1, "Vertical" );
	pause( dev, 2 );

	dev.setAutoscroll( hd44780::VSCROLL );
	dev.write( text, 150 );
	pause( dev, 1 );

	// Write the text with horizontal autoscrolling
	dev.write( 5, 1, "Horizontal" );
	pause( dev, 2 );

	dev.setAutoscroll( hd44780::HSCROLL );
	dev.write( text, 150 );
	pause( dev, 2 );

	// Write the text with horizontal autoscrolling (single line)
	dev.write( 1, 1, "Horizontal (line)" );
	pause( dev, 2 );

	dev.setAutoscroll( hd44780::HSCROLL_LINE );
	dev.write( text, 150 );
	pause( dev, 2 );

	// Write the text with horizontal (single line) and vertical autoscrolling
	dev.write( 0, 1, utils::align( "Horizontal (line) and vertical", 20, utils::ALIGN_CENTER ) );
	pause( dev, 2 );

	dev.setAutoscroll( hd44780::HSCROLL_LINE | hd44780::VSCROLL );
	dev.write( text, 150 );

	// Restore the autoscrolling
	dev.setAutoscroll( hd44780::VSCROLL );

	// Wait some time and clear the screen
	pause( dev, 2 );
}

void demo6( hd44780 &dev ) {

	// Write the title
	dev.write( 4, 1, "= Demo #6 =" );
	dev.write( 3, 2, "Word wrapping" );
	pause( dev, 2 );

	// A sample text
	std::string text =	"To be, or not to be, that is the question: "
						"whether 'tis nobler in the mind to suffer "
						"the slings and arrows of outrageous fortune, "
						"or to take arms against a sea of troubles, "
						"and, by opposing, end them. To die, to sleep...";

	// Write the text with word wrapping
	dev.write( utils::align( text, 20, utils::ALIGN_CENTER ), 200 );
	pause( dev, 2 );
}

void demo7( hd44780 &dev ) {

	// Write the title
	dev.write( 4, 1, "= Demo #7 =" );
	dev.write( 1, 2, "Custom characters" );
	pause( dev, 2 );

	// Display loading message
	dev.write( 5, 1, "Loading..." );

	// Define some custom characters
	uint8_t smile[8]		= { 0x00, 0x0a, 0x0a, 0x00, 0x00, 0x11, 0x0e, 0x00 };
	uint8_t heart[8]		= { 0x00, 0x0a, 0x1f, 0x1f, 0x1f, 0x0e, 0x04, 0x00 };
	uint8_t pacman[8]		= { 0x0e, 0x1d, 0x1f, 0x1c, 0x18, 0x1c, 0x1f, 0x0e };
	uint8_t music[8]		= { 0x03, 0x0d, 0x09, 0x09, 0x09, 0x0b, 0x1b, 0x18 };

	uint8_t bat_left[8]		= { 0x02, 0x06, 0x0f, 0x0f, 0x0f, 0x0f, 0x06, 0x02 };
	uint8_t bat_center[8]	= { 0x0a, 0x0e, 0x1f, 0x1f, 0x1f, 0x1f, 0x0e, 0x04 };
	uint8_t bat_right[8]	= { 0x08, 0x0c, 0x1e, 0x1e, 0x1e, 0x1e, 0x0c, 0x08 };

	dev.defChar( hd44780::CCHAR0, smile );
	dev.defChar( hd44780::CCHAR1, heart );
	dev.defChar( hd44780::CCHAR2, pacman );
	dev.defChar( hd44780::CCHAR3, music );

	dev.defChar( hd44780::CCHAR4, bat_left );
	dev.defChar( hd44780::CCHAR5, bat_center );
	dev.defChar( hd44780::CCHAR6, bat_right );

	// Clear the display
	dev.clear();

	// Write the custom characters
	dev.write( 1, 0, "Smile  " );
	dev.write( hd44780::CCHAR0 );

	dev.write( 12, 0, hd44780::CCHAR1 );
	dev.write( " Heart" );

	dev.write( 1, 1, "Pacman " );
	dev.write( hd44780::CCHAR2 );

	dev.write( 12, 1, hd44780::CCHAR3 );
	dev.write( " Music" );

	dev.write( 4, 3, "Batman! " );
	dev.write( hd44780::CCHAR4 );
	dev.write( hd44780::CCHAR5 );
	dev.write( hd44780::CCHAR6 );

	// Wait some time and clear the screen
	pause( dev, 6 );
}

void demo8( hd44780 &dev ) {

	// Write the title
	dev.write( 4, 1, "= Demo #8 =" );
	dev.write( 1, 2, "Print current time" );
	pause( dev, 2 );

	// Write the current date
	size_t i = 0;

	for ( ; i < 10; ++i ) {

		dev.write( 0, 1, utils::align( exec( "date +%H:%m:%S" ), 20, utils::ALIGN_CENTER ) );
		pause( dev, 1 );
	}

	// Wait some time and clear the screen
	pause( dev, 1 );
}

void demo9( hd44780 &dev ) {

	// Write the title
	dev.write( 4, 1, "= Demo #9 =" );
	dev.write( 3, 2, "Progress bars" );
	pause( dev, 2 );

	// Draw the progress bars
	float factor = 100.0 / 18.0;

	size_t i = 0;

	for ( ; i <= 100; i += 5 ) {

		dev.write( 0, 1, utils::align( utils::format( "%zu%%", i ), 20, utils::ALIGN_CENTER ) );
		dev.write( 1, 2, std::string( (size_t) math::abs( (float) i / factor ), (uint8_t) 0xFF ) );

		time::msleep( 500 );
	}

	pause( dev, 2 );

	for ( i = 0; i <= 100; i += 5 ) {

		dev.write( 0, 1, utils::align( utils::format( "%zu%%", i ), 20, utils::ALIGN_CENTER ) );
		dev.write( 0, 2, "[" + std::string( (size_t) math::abs( (float) i / factor ), '=' ) );
		dev.write( 19, 2, "]" );
	
		time::msleep( 500 );
	}

	// Wait some time and clear the screen
	pause( dev, 2 );
}

void demo10( hd44780 &dev ) {

	// Write the title
	dev.write( 3, 1, "= Demo #10 =" );
	dev.write( 1, 2, "Directory contents" );
	pause( dev, 2 );

	// Write the contents of the directory
	dev.write( "Directory contents\n" );
	dev.write( exec( "ls | awk '{print FNR \" \" $0}'" ), 200 );
	pause( dev, 2 );
}

void demo11( hd44780 &dev ) {

	// Write the title
	dev.write( 3, 1, "= Demo #11 =" );
	dev.write( 1, 2, "Wireless networks" );
	pause( dev, 2 );

	// Write the list of the wireless networks
	dev.write( 0, 0, "Scanning..." );
	std::string list = exec( "iwlist wlan0 scanning | sed -n 's/.*ESSID:\"\\(.*\\)\"/\\1/p' | awk '{ print FNR, $0 }'" );
	dev.clear();

	dev.write( "Wireless networks\n" );
	dev.write( list, 200 );

	// Wait some time and clear the screen
	time::sleep( 2 );
	dev.clear();
}

int
main( int argc, char *args[] ) {

	// Display controller
	hd44780 dev( 14, 18, 4, 17, 21, 22 );

	// Initialize the 16x2 display
	dev.init( 20, 4 );

	// Print the initial messages
	dev.write( utils::align(

		"= Rpi-hw =\n"
		"Interfacing Raspberry Pi with Hitachi HD44780",

	20, utils::ALIGN_CENTER ) );

	pause( dev, 5 );

	dev.write( utils::align(

		"Rpi-hw is a free C++ library designed to manage "
		"the Raspberry Pi's GPIO connector.",

	20, utils::ALIGN_CENTER ), 200 );

	pause( dev, 2 );

	// Play all demos
	demo0( dev );
	demo1( dev );
	demo2( dev );
	demo3( dev );
	demo4( dev );
	demo5( dev );
	demo6( dev );
	demo7( dev );
	demo8( dev );
	demo9( dev );
	demo10( dev );
	//demo11( dev );

	// Print the final message
	dev.write( utils::align( "That's all, folks!\nFeel free to comment my work!", 20, utils::ALIGN_CENTER ), 200 );
	pause( dev, 2 );
	dev.write( utils::align( "For more informations visit:\n\nwww.hackyourmind.org", 20, utils::ALIGN_CENTER ), 200 );
	pause( dev, 2 );

	/*
	dev.write( utils::align( "A special thanks to my friend Nicola for helping me with this video!", 20, utils::ALIGN_CENTER ), 200 );
	dev.write( hd44780::CCHAR0 );
	pause( dev, 2 );
	*/

	return 0;
}

