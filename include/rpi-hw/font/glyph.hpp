/* 
    Title --- font/glyph.hpp

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


#ifndef _RPI_HW_FONT_GLYPH_HPP_
#define _RPI_HW_FONT_GLYPH_HPP_

#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>

namespace rpihw { // Begin main namespace

namespace font { // Begin fonts namespace

//! The format of pixels in the bitmap buffer.
enum PixelMode {

	PIXEL_MODE_NONE 	= 0,
	PIXEL_MODE_MONO		= 1,
	PIXEL_MODE_GRAY		= 2,
	PIXEL_MODE_GRAY2	= 3,
	PIXEL_MODE_GRAY4	= 4,
	PIXEL_MODE_LCD		= 5,
	PIXEL_MODE_LCD_V	= 6
};

/*!
	@class glyph
	@brief Simple glyph structure.
*/
struct glyph {

	//! The width of the glyph.
	uint8_t width;
	//! The height of the glyph.
	uint8_t height;

	//! The left side bearing.
	int8_t left;
	//! The top side bearing.
	int8_t top;

	//! The format of the glyph bitmap (monochrome or gray).
	PixelMode format;
	//! Maximum gray level value (in the range 1 to 255).
	uint8_t grays;
	//! The number of bytes per bitmap line. May be positive or negative.
	int16_t pitch;

	//! The horizontal advance width in pixels.
	int8_t xadvance;
	//! The vertical advance height in pixels.
	int8_t yadvance;

	//! A pointer to the bitmap pixels.
	const uint8_t *buffer;
};

} // End of fonts namespace

} // End of main namespace

#endif /* _RPI_HW_GLYPH_HPP_ */
