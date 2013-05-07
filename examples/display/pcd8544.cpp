/* 
    Title --- pcd8544.cpp [examples]

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

#include <cstdlib>

#include <rpi-hw.hpp>

#include <rpi-hw/font/freetype.hpp>
#include <rpi-hw/image/bitmap.hpp>
#include <rpi-hw/display/pcd8544.hpp>

// Use some namespaces
using namespace rpihw;
using namespace rpihw::display;

void
showTitleScreen( pcd8544 &disp, font::base &title_font, font::base &text_font, const std::string &title, const std::string &text ) {

	disp.clear();

	// Draw the demo title
	disp.setFont( title_font );
	disp.drawText( title );

	// Draw the demo description
	disp.setFont( text_font );
	disp.drawText( 0, 12, text, 84, 48 );

	disp.redraw();

	time::sleep(4);

	disp.clear();
	disp.redraw();
}

void
drawLines( pcd8544 &disp ) {

	disp.clear();

	std::srand( std::time( NULL ) );

	int8_t x0, y0, x1, y1, i = 0;

	// Draw some random lines
	for ( ; i < 100; i++ ) {

		x0 = rand() % 84;
		y0 = rand() % 48;
		x1 = rand() % 84;
		y1 = rand() % 48;

		disp.drawLine( x0, y0, x1, y1 );
		disp.redraw();

		time::msleep(80);
	}

	time::sleep(1);

	disp.clear();
	disp.redraw();
}

void
drawCircles( pcd8544 &disp ) {

	disp.clear();

	std::srand( std::time( NULL ) );

	int8_t x, y, r, i = 0;

	// Draw some random circles
	for ( ; i < 100; i++ ) {

		x = rand() % 84;
		y = rand() % 48;
		r = rand() % 18 + 2;

		disp.drawCircle( x, y, r );
		disp.redraw();

		time::msleep(80);
	}

	time::sleep(1);

	disp.clear();
	disp.redraw();
}

void
drawRectangles( pcd8544 &disp ) {

	disp.clear();

	std::srand( std::time( NULL ) );

	int8_t x, y, w, h, i = 0;

	// Draw some random rectangles
	for ( ; i < 100; i++ ) {

		x = rand() % 84;
		y = rand() % 48;
		w = rand() % 30;
		h = rand() % 25 + 5;

		disp.drawRect( x, y, x + w, y + h );
		disp.redraw();

		time::msleep(80);
	}

	time::sleep(1);

	disp.clear();
	disp.redraw();
}

void
drawEllipses( pcd8544 &disp ) {

	disp.clear();

	std::srand( std::time( NULL ) );

	int8_t x, y, a, b, i = 0;

	// Draw some random ellipses
	for ( ; i < 100; i++ ) {

		x = rand() % 84;
		y = rand() % 48;
		a = rand() % 25 + 5;
		b = rand() % 25 + 5;

		disp.drawEllipse( x, y, a, b );
		disp.redraw();

		time::msleep(80);
	}

	time::sleep(1);

	disp.clear();
	disp.redraw();
}

void
showImage( pcd8544 &disp, const std::string &path, uint8_t x = 0, uint8_t y = 0 ) {

	disp.clear();

	// Load and show the image
	image::bitmap< bool > img( path );
	disp.drawImage( img, x, y );

	disp.redraw();
}

void
showDitherImage( pcd8544 &disp, const std::string &path, uint8_t x = 0, uint8_t y = 0 ) {

	disp.clear();

	// Load the image using Magick++ API and convert it to black and white 
	Magick::Image img_magick( path );
	img_magick.colorSpace( Magick::GRAYColorspace );
	img_magick.randomThreshold( Magick::Geometry( 4, 4 ) );

	image::bitmap< bool > img( img_magick );

	// Draw the image on the screen
	disp.drawImage( img, x, y );

	disp.redraw();
}

void
showFontStyles( pcd8544 &disp ) {

	// Load some text font
	font::freetype normal( "fonts/DroidSerif-Regular.ttf", 12, font::RENDER_MONOCHROME );
	font::freetype bold( "fonts/DroidSerif-Bold.ttf", 12, font::RENDER_MONOCHROME );
	font::freetype oblique( "fonts/DroidSerif-Italic.ttf", 12, font::RENDER_MONOCHROME );

	disp.clear();

	// Draw same text using different styles
	disp.setFont( normal );
	disp.drawText( "Hello world\n" );

	disp.setFont( bold );
	disp.drawText( "Hello world\n" );

	disp.setFont( oblique );
	disp.drawText( "Hello world" );

	disp.redraw();
}

void
showFontSizes( pcd8544 &disp ) {

	// Load a font
	font::freetype regular( "fonts/DroidSerif-Regular.ttf", 10, font::RENDER_MONOCHROME );
	disp.setFont( regular );

	// Draw same text using different sizes
	uint8_t i = 12;

	for ( ; i < 46; i += 2 ) {

		regular.setSize( i );

		disp.clear();
		disp.drawText( 0, 0, "Size" );
		disp.redraw();

		time::msleep(250);
	}
}

void
showFontTest( pcd8544 &disp, font::base &font ) {

	disp.clear();

	disp.setFont( font );
	disp.drawText( "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", 84, 48, pcd8544::WORD_BREAK );

	disp.redraw();
}

void
showUnicode( pcd8544 &disp ) {

	// Load some fonts
	font::freetype greek( "fonts/DroidSans.ttf", 12, font::RENDER_MONOCHROME );
	font::freetype cjk( "fonts/DroidSansFallback.ttf", 12, font::RENDER_MONOCHROME );

	std::u32string utf32_text;

	// Draw greek text
	disp.setFont( greek );
	utf32_text = U"Γεια σας κόσμο\n";
	disp.drawText( utf32_text );

	// Draw japanese text
	disp.setFont( cjk );
	utf32_text = U"こんにちは世界\n";
	disp.drawText( utf32_text );

	// Draw chinese text
	utf32_text = U"世界，你好";
	disp.drawText( utf32_text );

	disp.redraw();
}

void
showAlignments( pcd8544 &disp, font::base &font ) {

	disp.setFont( font );

	// Show text alignments
	std::string text = "More importantly, a towel has immense psychological value.";

	disp.clear();
	disp.drawText( 0, 0, text, 84, 48, pcd8544::ALIGN_LEFT );
	disp.redraw();

	time::sleep(3);

	disp.clear();
	disp.drawText( 0, 0, text, 84, 48, pcd8544::ALIGN_CENTER );
	disp.redraw();

	time::sleep(3);

	disp.clear();
	disp.drawText( 0, 0, text, 84, 48, pcd8544::ALIGN_RIGHT );
	disp.redraw();

	time::sleep(3);
}

void
showStarWars( pcd8544 &disp, font::base &font ) {

	disp.clear();

	// Show a tribute to Star Wars
	showImage( disp, "images/starwars.png" );
	time::sleep(2);

	disp.clear();

	disp.setFont( font );

	std::string opening =

		"It is a period of civil war. Rebel "
		"spaceships, striking from a hidden "
		"base, have won their first victory "
		"against the evil Galactic Empire. [...]";

	int8_t i = 48;

	for ( ; i > -90; --i ) {

		disp.clear();
		disp.drawText( 0, i, opening, 84, 127, pcd8544::ALIGN_CENTER );
		disp.redraw();

		time::msleep(300);
	}
}

void
showRadar( pcd8544 &disp, font::base &font ) {

	// Set the text font
	disp.setFont( font );

	// Target
	int8_t x = -10, y = 25;

	float distance;

	// Move the target
	for ( ; x < 94; x += 2 ) {

		// Calculate the distance between points
		distance = math::sqrt( math::square( (float) x - 42.0 ) + math::square( (float) y ) );

		// Redraw the screen
		disp.clear();

		disp.fillCircle( 42, 0, 2 );
		disp.drawCircle( 42, 0, 15 );

		if ( x >= 0 && x < 84 ) {

			disp.drawCircle( x, y, 3 );
			disp.drawLine( 42, 0, x, y );

			disp.drawText( x - 10, y + 3, utils::format( "%.1fm", distance ) );
		}

		disp.drawRect( 0, 0, 83, 47 );
		disp.redraw();

		// Wait some time
		time::msleep( 500 );
	}
}

int
main( int argc, char *args[] ) {

	// Load the main font
	font::freetype title_font( "fonts/DroidSerif-Bold.ttf", 12, font::RENDER_MONOCHROME );
	font::freetype body_font( "fonts/DroidSans.ttf", 10, font::RENDER_MONOCHROME );

	// Create the display controller
	pcd8544 disp( 23, 24, 25, 8, 7 );

	// Initialize the display
	disp.init();

	// Show the main logo
	showImage( disp, "images/main_logo.png" );
	time::sleep(3);


	/* ========= Demo #0 ========= */

	showTitleScreen( disp, title_font, body_font, "Demo #0", "Drawing functions" );
	time::sleep(1);

	drawLines( disp );
	time::sleep(1);

	drawCircles( disp );
	time::sleep(1);

	drawRectangles( disp );
	time::sleep(1);

	drawEllipses( disp );
	time::sleep(2);


	/* ========= Demo #1 ========= */

	showTitleScreen( disp, title_font, body_font, "Demo #1", "Handles multiple image formats using Magick++ API" );
	time::sleep(1);

	showImage( disp, "images/tao.png", 18, 0 );
	time::sleep(2);

	showDitherImage( disp, "images/eye.png" );
	time::sleep(2);

	showDitherImage( disp, "images/hand.gif", 21, 0 );
	time::sleep(2);

	showDitherImage( disp, "images/cat.jpg", 6, 0 );
	time::sleep(2);


	/* ========= Demo #2 ========= */

	showTitleScreen( disp, title_font, body_font, "Demo #2", "Supports several font formats using FreeType library" );
	time::sleep(1);

	showFontStyles( disp );
	time::sleep(2);

	showFontSizes( disp );
	time::sleep(2);

	showFontTest( disp, body_font );
	time::sleep(2);


	/* ========= Demo #3 ========= */

	showTitleScreen( disp, title_font, body_font, "Demo #3", "Unicode support using UTF8-CPP library" );
	time::sleep(1);

	showUnicode( disp );
	time::sleep(4);


	/* ========= Demo #4 ========= */

	showTitleScreen( disp, title_font, body_font, "Demo #4", "Text wrapping" );
	time::sleep(1);

	showAlignments( disp, body_font );
	time::sleep(2);


	/* ========= Demo #5 ========= */

	showTitleScreen( disp, title_font, body_font, "Demo #5", "A long time ago, in a galaxy far, far away..." );
	time::sleep(1);

	showStarWars( disp, body_font );
	time::sleep(2);


	/* ========= Demo #6 ========= */

	showTitleScreen( disp, title_font, body_font, "Demo #6", "The target is approaching" );
	time::sleep(1);

	showRadar( disp, body_font );
	time::sleep(2);

	disp.clear();
	disp.redraw();

	return 0;
}

