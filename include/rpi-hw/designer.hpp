/* 
    Title --- designer.hpp

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


#ifndef _RPI_HW_DESIGNER_HPP_
#define _RPI_HW_DESIGNER_HPP_

#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>
#include <rpi-hw/math.hpp>


// FIXME FIXME FIXME FIXME
// FIXME FIXME FIXME FIXME
#include <rpi-hw/bitmap.hpp>
#include <rpi-hw/bitmap-inl.hpp>

#include <rpi-hw/font/glyph.hpp>

#include <rpi-hw/font/base.hpp>
#include <rpi-hw/font/base-inl.hpp>

#include <rpi-hw/font/freetype.hpp>
#include <rpi-hw/font/freetype-inl.hpp>
// FIXME FIXME FIXME FIXME
// FIXME FIXME FIXME FIXME


namespace rpihw { // Begin main namespace

/*!
	@class designer
	@brief The graphic designer.
*/
template < typename T, typename Color >
class designer {

public:

	//! Type of alignment.
	enum TextAlign {

		ALIGN_LEFT		= 0x00,
		ALIGN_CENTER	= 0x01,
		ALIGN_RIGHT		= 0x02
	};

	/*!
		@brief Constructor method.
		@param[in] interface The instance of the interface.
		@param[in] set The method to set a pixel color.
		@param[in] get The method to get a pixel color.
	*/
	designer( T width, T height );

	//! Destructor method.
	virtual ~designer();

	/*!
		@brief Sets the foreground color.
		@param[in] color The foreground color.
	*/
	virtual void setColor( Color color );

	/*!
		@brief Gets the current foreground color.
		@return The current foreground color.
	*/
	virtual Color getColor() const;

	/*!
		@brief Sets the color of a pixel using the current foreground color.
		@param[in] x The horizontal position of the pixel.
		@param[in] y The vertical position of the pixel.
	*/
	virtual void setPixel( T x, T y );

	/*!
		@brief Sets the color of a pixel.
		@param[in] x The horizontal position of the pixel.
		@param[in] y The vertical position of the pixel.
		@param[in] color The new color of the pixel.
	*/
	virtual void setPixel( T x, T y, Color color ) = 0;

	/*!
		@brief Sets the color of a pixel.
		@param[in] x The horizontal position of the pixel.
		@param[in] y The vertical position of the pixel.
		@return The current color of the pixel.
	*/
	virtual Color getPixel( T x, T y ) const = 0;

	/*!
		@brief Draws a line.
		@param[in] x0 The horizontal position of the first point of the line.
		@param[in] y0 The vertical position of the first point of the line.
		@param[in] x1 The horizontal position of the second point of the line.
		@param[in] y1 The vertical position of the second point of the line.
	*/
	virtual void drawLine( T x0, T y0, T x1, T y1 );

	/*!
		@brief Draws a rectangle.
		@param[in] x0 The horizontal position of the left-top vertex of the rectangle.
		@param[in] y0 The vertical position of the left-top vertex of the rectangle.
		@param[in] x1 The horizontal position of the right-bottom vertex of the rectangle.
		@param[in] y1 The vertical position of the right-bottom vertex of the rectangle.
	*/
	virtual void drawRect( T x0, T y0, T x1, T y1 );

	/*!
		@brief Draws a circle.
		@param[in] cx The horizontal position of the center of the circle.
		@param[in] cy The vertical position of the center of the circle.
		@param[in] radius The radius of the circle.
	*/
	virtual void drawCircle( T cx, T cy, T radius );

	/*!
		@brief Draws an ellipse.
		@param[in] cx The horizontal position of the center of the ellipse.
		@param[in] cy The vertical position of the center of the ellipse.
		@param[in] a The parameters `a` of the ellipse.
		@param[in] b The parameters `b` of the ellipse.
	*/
	virtual void drawEllipse( T cx, T cy, T a, T b );

	/*!
		@brief Draws a filled rectangle.
		@param[in] x0 The horizontal position of the left-top vertex.
		@param[in] y0 The vertical position of the left-top vertex.
		@param[in] x1 The horizontal position of the right-bottom vertex.
		@param[in] y1 The vertical position of the right-bottom vertex.
	*/
	virtual void fillRect( T x0, T y0, T x1, T y1 );

	/*!
		@brief Draws a filled circle.
		@param[in] cx The horizontal position of the center of the circle.
		@param[in] cy The vertical position of the center of the circle.
		@param[in] radius The radius of the circle.
	*/
	virtual void fillCircle( T cx, T cy, T radius );

	/*!
		@brief Draws a filled ellipse.
		@param[in] cx The horizontal position of the center of the ellipse.
		@param[in] cy The vertical position of the center of the ellipse.
		@param[in] a The parameters `a` of the ellipse.
		@param[in] b The parameters `b` of the ellipse.
	*/
	virtual void fillEllipse( T cx, T cy, T a, T b );

	/*!
		@brief Draws a bitmap image.
		@param[in] img The bitmap object.
		@param[in] x The horizontal position of the left-top vertex.
		@param[in] y The vertical position of the left-top vertex.
	*/
	virtual void drawBitmap( const bitmap &img, T x, T y );

	/*!
		@brief Sets the position of the cursor.
		@param[in] x The new horizontal position of the cursor.
		@param[in] y The new vertical position of the cursor.
	*/
	virtual void move( T x, T y );

	//! Moves the cursor to the new line.
	virtual void newLine();

	/*!
		@brief Writes a character.
		@param[in] charcode The 8-bit character.
	*/
	virtual void write( uint8_t charcode );

	/*!
		@brief Moves the cursor position and writes a character.
		@param[in] x The new horizontal position of the cursor.
		@param[in] y The new vertical position of the cursor.
		@param[in] charcode The 8-bit character.
	*/
	virtual void write( T x, T y, uint8_t charcode );

	/*!
		@brief Writes a string.
		@param[in] text The string to be written.
	*/
	virtual void write( const std::string &text );


	// FIXME FIXME FIXME
	/*!
		@brief Writes a multiline string.
		@param[in] text The string to be written.
		@param[in] width The width of the text area.
		@param[in] height The height of the text area.
		@param[in] align The position of the alignment.
	*/
	virtual void write( const std::string &text, T width, T height, TextAlign align );
	// FIXME FIXME FIXME


	/*!
		@brief Moves the cursor position and writes a string.
		@param[in] x The new horizontal position of the cursor.
		@param[in] y The new vertical position of the cursor.
		@param[in] text The string to be written.
	*/
	virtual void write( T x, T y, const std::string &text );

protected:

	//! Size of the drawing area.
	vec2< T > m_area;

	//! Foreground color.
	Color m_color;

	//! Cursor position.
	vec2< T > m_pos;

	//! Text font.
	font::base *m_font;

	//! Draws the symmetric points of the circle.
	virtual void drawCirclePoints( T cx, T cy, T x, T y );

	//! Draws the symmetric areas of the circle.
	virtual void drawCircleAreas( T cx, T cy, T x, T y );

	//! Draws the symmetric points of the ellipse.
	virtual void drawEllipsePoints( T cx, T cy, T x, T y );

	//! Draws the symmetric areas of the ellipse.
	virtual void drawEllipseAreas( T cx, T cy, T x, T y );

	/*!
		@brief Checks if the current line is full.
		@param[in] chr The character.
	*/
	bool isLineFull( uint8_t chr );
};

} // End of main namespace

#endif
