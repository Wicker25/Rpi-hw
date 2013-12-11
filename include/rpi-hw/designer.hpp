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

#include <algorithm>
#include <vector>
#include <locale>

#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>
#include <rpi-hw/math.hpp>

#include <rpi-hw/font/glyph.hpp>
#include <rpi-hw/font/base.hpp>
#include <rpi-hw/image/base.hpp>

namespace rpihw { // Begin main namespace

/*!
	@class designer
	@brief The graphic designer.
*/
template < typename T, typename C, uint8_t N = 3 >
class designer {

public:

	//! Parameters of text.
	enum TextFlags {

		ALIGN_LEFT		= 0x01,
		ALIGN_CENTER	= 0x02,
		ALIGN_RIGHT		= 0x04,
		WORD_WRAP		= 0x08,
		WORD_BREAK		= 0x10
	};

	/*!
		@brief Constructor method.
		@param[in] width The width of the drawing area.
		@param[in] height The height of the drawing area.
	*/
	designer( T width, T height );

	//! Destructor method.
	virtual ~designer();

	/*!
		@brief Sets the pen color.
		@param[in] color A pointer to the color data.
	*/
	void setPenColor( const std::vector< C > &color );

	/*!
		@brief Gets the current pen color.
		@return The pointer to the color data.
	*/
	const std::vector< C > &getPenColor() const;

	/*!
		@brief Sets the pen position.
		@param[in] x The new horizontal pen position.
		@param[in] y The new vertical pen position.
	*/
	virtual void setPenPosition( T x, T y );

	/*!
		@brief Sets the text font.
		@param[in] font The new text font.
	*/
	void setFont( font::base &font );

	/*!
		@brief Returns the current text font.
		@return The text font.
	*/
	font::base &getFont() const;

	/*!
		@brief Draws a point.
		@param[in] x The horizontal position of the point.
		@param[in] y The vertical position of the point.
	*/
	void drawPoint( T x, T y );

	/*!
		@brief Draws a line.
		@param[in] x0 The horizontal position of the first point of the line.
		@param[in] y0 The vertical position of the first point of the line.
		@param[in] x1 The horizontal position of the second point of the line.
		@param[in] y1 The vertical position of the second point of the line.
	*/
	void drawLine( T x0, T y0, T x1, T y1 );

	/*!
		@brief Draws a rectangle.
		@param[in] x0 The horizontal position of the left-top vertex of the rectangle.
		@param[in] y0 The vertical position of the left-top vertex of the rectangle.
		@param[in] x1 The horizontal position of the right-bottom vertex of the rectangle.
		@param[in] y1 The vertical position of the right-bottom vertex of the rectangle.
	*/
	void drawRect( T x0, T y0, T x1, T y1 );

	/*!
		@brief Draws a circle.
		@param[in] cx The horizontal position of the center of the circle.
		@param[in] cy The vertical position of the center of the circle.
		@param[in] radius The radius of the circle.
	*/
	void drawCircle( T cx, T cy, T radius );

	/*!
		@brief Draws an ellipse.
		@param[in] cx The horizontal position of the center of the ellipse.
		@param[in] cy The vertical position of the center of the ellipse.
		@param[in] a The parameters `a` of the ellipse.
		@param[in] b The parameters `b` of the ellipse.
	*/
	void drawEllipse( T cx, T cy, T a, T b );

	/*!
		@brief Draws a filled rectangle.
		@param[in] x0 The horizontal position of the left-top vertex.
		@param[in] y0 The vertical position of the left-top vertex.
		@param[in] x1 The horizontal position of the right-bottom vertex.
		@param[in] y1 The vertical position of the right-bottom vertex.
	*/
	void fillRect( T x0, T y0, T x1, T y1 );

	/*!
		@brief Draws a filled circle.
		@param[in] cx The horizontal position of the center of the circle.
		@param[in] cy The vertical position of the center of the circle.
		@param[in] radius The radius of the circle.
	*/
	void fillCircle( T cx, T cy, T radius );

	/*!
		@brief Draws a filled ellipse.
		@param[in] cx The horizontal position of the center of the ellipse.
		@param[in] cy The vertical position of the center of the ellipse.
		@param[in] a The parameters `a` of the ellipse.
		@param[in] b The parameters `b` of the ellipse.
	*/
	void fillEllipse( T cx, T cy, T a, T b );

	/*!
		@brief Draws an image.
		@param[in] img The image object.
	*/
	void drawImage( const image::base< C > &img );

	/*!
		@brief Moves the pen position and draws an image.
		@param[in] x The horizontal position of the left-top vertex.
		@param[in] y The vertical position of the left-top vertex.
		@param[in] img The image object.
	*/
	void drawImage( T x, T y, const image::base< C > &img );

	/*!
		@brief Draws a character.
		@param[in] charcode The character code.
	*/
	void drawText( char32_t charcode );

	/*!
		@brief Moves the pen position and draws a character.
		@param[in] x The new horizontal pen position.
		@param[in] y The new vertical pen position.
		@param[in] charcode The character code.
	*/
	void drawText( T x, T y, char32_t charcode );

	/*!
		@brief Draws a string.
		@param[in] it The start of the string.
		@param[in] end The end of the string.
	*/
	template < typename iterator >
	void drawText( iterator it, iterator end );

	/*!
		@brief Draws a multiline string.
		@param[in] it The start of the string.
		@param[in] end The end of the string.
		@param[in] width The width of the text area.
		@param[in] height The height of the text area.
		@param[in] flags The parameters of the text.
	*/
	template < typename iterator >
	void drawText( iterator it, iterator end, T width, T height, uint8_t flags );

	/*!
		@brief Moves the pen position and draws a string.
		@param[in] x The new horizontal pen position.
		@param[in] y The new vertical pen position.
		@param[in] it The start of the string.
		@param[in] end The end of the string.
	*/
	template < typename iterator >
	void drawText( T x, T y, iterator it, iterator end );

	/*!
		@brief Moves the pen position and draws a multiline string.
		@param[in] x The new horizontal pen position.
		@param[in] y The new vertical pen position.
		@param[in] it The start of the string.
		@param[in] end The end of the string.
		@param[in] width The width of the text area.
		@param[in] height The height of the text area.
		@param[in] flags The parameters of the text.
	*/
	template < typename iterator >
	void drawText( T x, T y, iterator it, iterator end, T width, T height, uint8_t flags );

	/*!
		@brief Draws a string.
		@param[in] text The string to be written.
	*/
	void drawText( const std::string &text );

	/*!
		@brief Draws a multiline string.
		@param[in] text The string to be written.
		@param[in] width The width of the text area.
		@param[in] height The height of the text area.
		@param[in] flags The parameters of the text.
	*/
	void drawText( const std::string &text, T width, T height, uint8_t flags = ALIGN_LEFT );

	/*!
		@brief Moves the pen position and draws a string.
		@param[in] x The new horizontal pen position.
		@param[in] y The new vertical pen position.
		@param[in] text The string to be written.
	*/
	void drawText( T x, T y, const std::string &text );

	/*!
		@brief Moves the pen position and draws a multiline string.
		@param[in] x The new horizontal pen position.
		@param[in] y The new vertical pen position.
		@param[in] text The string to be written.
		@param[in] width The width of the text area.
		@param[in] height The height of the text area.
		@param[in] flags The parameters of the text.
	*/
	void drawText( T x, T y, const std::string &text, T width, T height, uint8_t flags = ALIGN_LEFT );

	/*!
		@brief Draws a unicode string.
		@param[in] text The string to be written.
	*/
	void drawText( const std::u32string &text );

	/*!
		@brief Draws a multiline unicode string.
		@param[in] text The string to be written.
		@param[in] width The width of the text area.
		@param[in] height The height of the text area.
		@param[in] flags The parameters of the text.
	*/
	void drawText( const std::u32string &text, T width, T height, uint8_t flags = ALIGN_LEFT );

	/*!
		@brief Moves the pen position and draws a unicode string.
		@param[in] x The new horizontal pen position.
		@param[in] y The new vertical pen position.
		@param[in] text The string to be written.
	*/
	void drawText( T x, T y, const std::u32string &text );

	/*!
		@brief Moves the pen position and draws a multiline unicode string.
		@param[in] x The new horizontal pen position.
		@param[in] y The new vertical pen position.
		@param[in] text The string to be written.
		@param[in] width The width of the text area.
		@param[in] height The height of the text area.
		@param[in] flags The parameters of the text.
	*/
	void drawText( T x, T y, const std::u32string &text, T width, T height, uint8_t flags = ALIGN_LEFT );

protected:

	//@{
	//! Size of the drawing area.
	T m_area_w, m_area_h;
	//@}

	//@{
	//! Pen position.
	T m_pos_x, m_pos_y;
	//@}

	//! Foreground color.
	std::vector< C > m_color;

	//! Text font.
	font::base *m_font;

	/*!
		@brief Draws a pixel.
		@param[in] x The horizontal position of the pixel.
		@param[in] y The vertical position of the pixel.
		@param[in] color An iterator to the color data.
	*/
	virtual void drawPixel( T x, T y, color_iterator< C > color ) = 0;

	/*!
		@brief Draws a character.
		@param[in] charcode The character code.
	*/
	void drawChar( char32_t charcode );

	//! Draws the symmetric points of the circle.
	void drawCirclePoints( T cx, T cy, T x, T y );

	//! Draws the symmetric areas of the circle.
	void drawCircleAreas( T cx, T cy, T x, T y );

	//! Draws the symmetric points of the ellipse.
	void drawEllipsePoints( T cx, T cy, T x, T y );

	//! Draws the symmetric areas of the ellipse.
	void drawEllipseAreas( T cx, T cy, T x, T y );
};

} // End of main namespace


// Include inline methods 
#include <rpi-hw/designer-inl.hpp>

#endif /* _RPI_HW_DESIGNER_HPP_ */
