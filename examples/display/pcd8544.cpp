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

// Include Rpi-hw headers
#include <rpi-hw.hpp>
#include <rpi-hw/font/freetype.hpp>
#include <rpi-hw/image/bitmap.hpp>
#include <rpi-hw/display/pcd8544.hpp>

// Use some namespaces
using namespace rpihw;
using namespace rpihw::display;

void
showTitleScreen( pcd8544 &dev, font::base &title_font, font::base &text_font, const std::string &title, const std::string &text ) {

	dev.clear();

	// Draw the demo title
	dev.setFont( title_font );
	dev.drawText( title );

	// Draw the demo description
	dev.setFont( text_font );
	dev.drawText( 0, 12, text, 84, 48 );

	dev.redraw();

	time::sleep(4);

	dev.clear();
	dev.redraw();
}

void
drawLines( pcd8544 &dev ) {

	dev.clear();

	std::srand( std::time( NULL ) );

	int8_t x0, y0, x1, y1, i = 0;

	// Draw some random lines
	for ( ; i < 100; i++ ) {

		x0 = rand() % 84;
		y0 = rand() % 48;
		x1 = rand() % 84;
		y1 = rand() % 48;

		dev.drawLine( x0, y0, x1, y1 );
		dev.redraw();

		time::msleep(80);
	}

	time::sleep(1);

	dev.clear();
	dev.redraw();
}

void
drawCircles( pcd8544 &dev ) {

	dev.clear();

	std::srand( std::time( NULL ) );

	int8_t x, y, r, i = 0;

	// Draw some random circles
	for ( ; i < 100; i++ ) {

		x = rand() % 84;
		y = rand() % 48;
		r = rand() % 18 + 2;

		dev.drawCircle( x, y, r );
		dev.redraw();

		time::msleep(80);
	}

	time::sleep(1);

	dev.clear();
	dev.redraw();
}

void
drawRectangles( pcd8544 &dev ) {

	dev.clear();

	std::srand( std::time( NULL ) );

	int8_t x, y, w, h, i = 0;

	// Draw some random rectangles
	for ( ; i < 100; i++ ) {

		x = rand() % 84;
		y = rand() % 48;
		w = rand() % 30;
		h = rand() % 25 + 5;

		dev.drawRect( x, y, x + w, y + h );
		dev.redraw();

		time::msleep(80);
	}

	time::sleep(1);

	dev.clear();
	dev.redraw();
}

void
drawEllipses( pcd8544 &dev ) {

	dev.clear();

	std::srand( std::time( NULL ) );

	int8_t x, y, a, b, i = 0;

	// Draw some random ellipses
	for ( ; i < 100; i++ ) {

		x = rand() % 84;
		y = rand() % 48;
		a = rand() % 25 + 5;
		b = rand() % 25 + 5;

		dev.drawEllipse( x, y, a, b );
		dev.redraw();

		time::msleep(80);
	}

	time::sleep(1);

	dev.clear();
	dev.redraw();
}

void
showImage( pcd8544 &dev, const std::string &path, uint8_t x = 0, uint8_t y = 0 ) {

	dev.clear();

	// Load and show the image
	image::bitmap< bool > img( path );
	dev.drawImage( x, y, img );

	dev.redraw();
}

void
showDitherImage( pcd8544 &dev, const std::string &path, uint8_t x = 0, uint8_t y = 0 ) {

	dev.clear();

	// Load the image using Magick++ API and convert it to black and white 
	Magick::Image img_magick( path );
	img_magick.colorSpace( Magick::GRAYColorspace );
	img_magick.randomThreshold( Magick::Geometry( 4, 4 ) );

	image::bitmap< bool > img( img_magick );

	// Draw the image on the screen
	dev.drawImage( x, y, img );

	dev.redraw();
}

void
showFontStyles( pcd8544 &dev ) {

	// Load some text font
	font::freetype normal( "fonts/DroidSerif-Regular.ttf", 12, font::RENDER_MONOCHROME );
	font::freetype bold( "fonts/DroidSerif-Bold.ttf", 12, font::RENDER_MONOCHROME );
	font::freetype oblique( "fonts/DroidSerif-Italic.ttf", 12, font::RENDER_MONOCHROME );

	dev.clear();

	// Draw same text using different styles
	dev.setFont( normal );
	dev.drawText( "Hello world\n" );

	dev.setFont( bold );
	dev.drawText( "Hello world\n" );

	dev.setFont( oblique );
	dev.drawText( "Hello world" );

	dev.redraw();
}

void
showFontSizes( pcd8544 &dev ) {

	// Load a font
	font::freetype regular( "fonts/DroidSerif-Regular.ttf", 10, font::RENDER_MONOCHROME );
	dev.setFont( regular );

	// Draw same text using different sizes
	uint8_t i = 12;

	for ( ; i < 46; i += 2 ) {

		regular.setSize( i );

		dev.clear();
		dev.drawText( 0, 0, "Size" );
		dev.redraw();

		time::msleep(250);
	}
}

void
showFontTest( pcd8544 &dev, font::base &font ) {

	dev.clear();

	dev.setFont( font );
	dev.drawText( "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", 84, 48, pcd8544::WORD_BREAK );

	dev.redraw();
}

void
showUnicode( pcd8544 &dev ) {

	// Load some fonts
	font::freetype greek( "fonts/DroidSans.ttf", 12, font::RENDER_MONOCHROME );
	font::freetype cjk( "fonts/DroidSansFallback.ttf", 12, font::RENDER_MONOCHROME );

	std::u32string utf32_text;

	// Draw greek text
	dev.setFont( greek );
	utf32_text = U"Γεια σας κόσμο\n";
	dev.drawText( utf32_text );

	// Draw japanese text
	dev.setFont( cjk );
	utf32_text = U"こんにちは世界\n";
	dev.drawText( utf32_text );

	// Draw chinese text
	utf32_text = U"世界，你好";
	dev.drawText( utf32_text );

	dev.redraw();
}

void
showAlignments( pcd8544 &dev, font::base &font ) {

	dev.setFont( font );

	// Show text alignments
	std::string text = "More importantly, a towel has immense psychological value.";

	dev.clear();
	dev.drawText( 0, 0, text, 84, 48, pcd8544::ALIGN_LEFT );
	dev.redraw();

	time::sleep(3);

	dev.clear();
	dev.drawText( 0, 0, text, 84, 48, pcd8544::ALIGN_CENTER );
	dev.redraw();

	time::sleep(3);

	dev.clear();
	dev.drawText( 0, 0, text, 84, 48, pcd8544::ALIGN_RIGHT );
	dev.redraw();

	time::sleep(3);
}

void
showStarWars( pcd8544 &dev, font::base &font ) {

	dev.clear();

	// Show a tribute to Star Wars
	showImage( dev, "images/starwars.png" );
	time::sleep(2);

	dev.clear();

	dev.setFont( font );

	std::string opening =

		"It is a period of civil war. Rebel "
		"spaceships, striking from a hidden "
		"base, have won their first victory "
		"against the evil Galactic Empire. [...]";

	int8_t i = 48;

	for ( ; i > -90; --i ) {

		dev.clear();
		dev.drawText( 0, i, opening, 84, 127, pcd8544::ALIGN_CENTER );
		dev.redraw();

		time::msleep(300);
	}
}

void
showRadar( pcd8544 &dev, font::base &font ) {

	// Set the text font
	dev.setFont( font );

	// Target
	int8_t x = -10, y = 25;

	float distance;

	// Move the target
	for ( ; x < 94; x += 2 ) {

		// Calculate the distance between points
		distance = math::sqrt( math::square( (float) x - 42.0 ) + math::square( (float) y ) );

		// Redraw the screen
		dev.clear();

		dev.fillCircle( 42, 0, 2 );
		dev.drawCircle( 42, 0, 15 );

		if ( x >= 0 && x < 84 ) {

			dev.drawCircle( x, y, 3 );
			dev.drawLine( 42, 0, x, y );

			dev.drawText( x - 10, y + 3, utils::format( "%.1fm", distance ) );
		}

		dev.drawRect( 0, 0, 83, 47 );
		dev.redraw();

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
	pcd8544 dev( 23, 24, 25, 8, 7 );

	// Initialize the display
	dev.init();

	// Show the main logo
	showImage( dev, "images/main_logo.png" );
	time::sleep(3);


	/* ========= Demo #0 ========= */

	showTitleScreen( dev, title_font, body_font, "Demo #0", "Drawing functions" );
	time::sleep(1);

	drawLines( dev );
	time::sleep(1);

	drawCircles( dev );
	time::sleep(1);

	drawRectangles( dev );
	time::sleep(1);

	drawEllipses( dev );
	time::sleep(2);


	/* ========= Demo #1 ========= */

	showTitleScreen( dev, title_font, body_font, "Demo #1", "Handles multiple image formats using Magick++ API" );
	time::sleep(1);

	showImage( dev, "images/tao.png", 18, 0 );
	time::sleep(2);

	showDitherImage( dev, "images/eye.png" );
	time::sleep(2);

	showDitherImage( dev, "images/hand.gif", 21, 0 );
	time::sleep(2);

	showDitherImage( dev, "images/cat.jpg", 6, 0 );
	time::sleep(2);


	/* ========= Demo #2 ========= */

	showTitleScreen( dev, title_font, body_font, "Demo #2", "Supports several font formats using FreeType library" );
	time::sleep(1);

	showFontStyles( dev );
	time::sleep(2);

	showFontSizes( dev );
	time::sleep(2);

	showFontTest( dev, body_font );
	time::sleep(2);


	/* ========= Demo #3 ========= */

	showTitleScreen( dev, title_font, body_font, "Demo #3", "Unicode support using UTF8-CPP library" );
	time::sleep(1);

	showUnicode( dev );
	time::sleep(4);


	/* ========= Demo #4 ========= */

	showTitleScreen( dev, title_font, body_font, "Demo #4", "Text wrapping" );
	time::sleep(1);

	showAlignments( dev, body_font );
	time::sleep(2);


	/* ========= Demo #5 ========= */

	showTitleScreen( dev, title_font, body_font, "Demo #5", "A long time ago, in a galaxy far, far away..." );
	time::sleep(1);

	showStarWars( dev, body_font );
	time::sleep(2);


	/* ========= Demo #6 ========= */

	showTitleScreen( dev, title_font, body_font, "Demo #6", "The target is approaching" );
	time::sleep(1);

	showRadar( dev, body_font );
	time::sleep(2);

	dev.clear();
	dev.redraw();

	return 0;
}

