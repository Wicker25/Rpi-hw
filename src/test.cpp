/* 
    Title --- test.cpp [development]

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

#include <iostream>

#include "../include/rpi-hw.hpp"

#include "../include/rpi-hw/font/freetype.hpp"
#include "../include/rpi-hw/font/freetype-inl.hpp"

#include "../include/rpi-hw/bitset.hpp"
#include "../include/rpi-hw/bitset-inl.hpp"

#include "../include/rpi-hw/display/pcd8544.hpp"
#include "../include/rpi-hw/display/pcd8544-inl.hpp"

// Use some namespaces
using namespace rpihw;
using namespace rpihw::display;

int
main( int argc, char *args[] ) {

	// Create the display controller
	pcd8544 disp( 23, 24, 25, 8, 7 );

	disp.init( 80, false );

	//disp.write( "Hello world! :)" );

	uint8_t i;

	for ( i = 48; i <= 95; i++ )
		disp.write( i );

	for ( i = 97; i <= 125; i++ )
		disp.write( i );

	disp.redraw();

	return 0;



	/*
	font::freetype myFont( "/usr/share/fonts/TTF/DroidSans.ttf", 8, font::RENDER_MONOCHROME );

	uint8_t width, height;

	const uint8_t *data = myFont.data( 'A', width, height );
	*/

	//disp.write( "Hello world!" );

	/*
	std::string text =	"To be, or not to be, that is the question: "
						"whether 'tis nobler in the mind to suffer "
						"the slings and arrows of outrageous fortune, "
						"or to take arms against a sea of troubles, "
						"and, by opposing, end them. To die, to sleep...";

	disp.write( text, 84, 48, pcd8544::ALIGN_LEFT );
	disp.redraw();
	*/

	/*
	CImg< bool > img( "enso.gif" );
	disp.drawImage( img, 0, 0 );
	disp.redraw();
	*/

	/*
	uint8_t i = 48;

	for ( ; i < 150; i++ )
		disp.write( i );

	disp.redraw();
	*/

	/*
	disp.fillEllipse( 42, 24, 10, 20, pcd8544::BLACK );
	disp.fillEllipse( 42, 24, 30, 10, pcd8544::BLACK );
	//disp.fillEllipse( 42, 24, 40, 30, pcd8544::BLACK );
	disp.redraw();

	time::msleep( 1000 );
	disp.clear();

	disp.drawEllipse( 42, 24, 10, 20 );
	disp.drawEllipse( 42, 24, 30, 10 );
	disp.drawEllipse( 42, 24, 40, 30 );
	disp.redraw();
	*/

	/*
	int i;
	clock_t begin, end;
	double elapsed_secs;

	begin = clock();

	for ( i = 0; i < 1000; i++ ) {

		disp.fillEllipse( 42, 24, 10, 20 );
		disp.fillEllipse( 42, 24, 30, 10 );
		disp.fillEllipse( 42, 24, 40, 30 );
	}

	disp.redraw();

	end = clock();
	elapsed_secs = (double)(end - begin) / CLOCKS_PER_SEC;

	printf( "A: %f\n", elapsed_secs );

	time::msleep( 1000 );
	disp.clear();

	begin = clock();

	for ( i = 0; i < 100000; i++ ) {

		disp.drawEllipse( 42, 24, 10, 20 );
		disp.drawEllipse( 42, 24, 30, 10 );
		disp.drawEllipse( 42, 24, 40, 30 );
	}

	disp.redraw();

	end = clock();
	elapsed_secs = (double)(end - begin) / CLOCKS_PER_SEC;

	printf( "B: %f\n", elapsed_secs );
	*/


	/*
	bitset image( 100, 1 );
	disp.drawBitmap( 0, 0, 10, image, pcd8544::BLACK );
	disp.redraw();
	*/

	/*
	disp.fillCircle( 20, 20, 10, pcd8544::BLACK );

	//disp.drawRect( 42 - 10, 24 - 10, 42 + 10, 24 + 10, pcd8544::BLACK );
	disp.drawCircle( 42, 24, 10, pcd8544::BLACK );
	disp.drawCircle( 42, 24, 3, pcd8544::BLACK );
	disp.drawCircle( 42, 24, 5, pcd8544::BLACK );

	disp.redraw();
	*/


	/*
	// TEST LINE
	int x = 41,
		y = 23;

	disp.drawLine( x, y, x - 10, y - 10, pcd8544::BLACK );
	disp.drawLine( x, y, x, y - 10, pcd8544::BLACK );
	disp.drawLine( x, y, x + 10, y - 10, pcd8544::BLACK );

	disp.drawLine( x, y, x - 10, y, pcd8544::BLACK );
	disp.drawLine( x, y, x, y, pcd8544::BLACK );
	disp.drawLine( x, y, x + 10, y, pcd8544::BLACK );

	disp.drawLine( x, y, x - 10, y + 10, pcd8544::BLACK );
	disp.drawLine( x, y, x, y + 10, pcd8544::BLACK );
	disp.drawLine( x, y, x + 10, y + 10, pcd8544::BLACK );

	disp.drawLine( 0, 0, 83, 47, pcd8544::BLACK );
	disp.drawLine( 83, 0, 0, 47, pcd8544::BLACK );

	disp.redraw();
	*/

	/*
	time::msleep( 500 );
	disp.fillEllipse( 3, 3, 83 - 3, 47 - 3, pcd8544::BLACK );
	disp.fillEllipse( 20, 20, 25, 25, pcd8544::WHITE );
	disp.redraw();
	*/

	/*
	time::msleep( 500 );
	disp.drawLine( 0, 0, 83, 47 );
	disp.drawLine( 83, 0, 0, 47 );
	disp.redraw();

	time::msleep( 500 );
	disp.drawLine( 60, 20, 60, 30 );
	disp.drawLine( 55, 25, 65, 25 );
	disp.redraw();

	time::msleep( 500 );
	disp.drawLine( 30, 30, 20, 20 );
	disp.drawLine( 30, 20, 20, 30 );
	disp.redraw();

	time::msleep( 500 );
	disp.drawRect( 0, 0, 83, 47 );
	disp.redraw();

	time::msleep( 500 );
	disp.fillRect( 10, 10, 30, 20 );
	disp.redraw();

	time::msleep( 500 );
	disp.drawEllipse( 3, 3, 83 - 3, 47 - 3 );
	disp.drawEllipse( 52, 35, 32, 15 );
	disp.redraw();
	*/


	/*
	// draw many lines
	int i;
	for (i=0; i<84; i+=4) {
		disp.drawLine(0, 0, i, 47, pcd8544::BLACK);
	}  
	for (i=0; i<48; i+=4) {
	disp.drawLine(0, 0, 83, i, pcd8544::BLACK);
	}
	disp.redraw();
	time::msleep(2000);
	disp.clear();

	// draw rectangles
	for (i=0; i<48; i+=2) {
	disp.drawRect(i, i, i + 96-i, i + 48-i, pcd8544::BLACK);
	}
	disp.redraw();
	time::msleep(2000);
	disp.clear();

	// draw multiple rectangles
	for (i=0; i<48; i++) {
	// alternate colors for moire effect
	disp.fillRect(i, i, i + 84-i, i + 48-i, i%2);
	}
	disp.redraw();
	time::msleep(2000);
	
	// draw mulitple circles
	for (i=0; i<48; i+=2) {
	LCDdrawcircle(41, 23, i, pcd8544::BLACK);
	}
	disp.redraw();
	time::msleep(2000);
	disp.clear();
	*/

	return 0;
}

