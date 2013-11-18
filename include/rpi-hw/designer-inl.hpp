/* 
    Title --- designer-inl.hpp

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


#ifndef _RPI_HW_DESIGNER_INL_HPP_
#define _RPI_HW_DESIGNER_INL_HPP_

namespace rpihw { // Begin main namespace

template < typename T, typename C, uint8_t N >
designer< T, C, N >::designer( T width, T height )

	: m_area_w	( width )
	, m_area_h	( height )
	, m_pos_x	(0)
	, m_pos_y	(0)
	, m_color	( N, 0 )
	, m_font	( nullptr ) {

}

template < typename T, typename C, uint8_t N >
designer< T, C, N >::~designer() {

}

template < typename T, typename C, uint8_t N >
inline void
designer< T, C, N >::setPenColor( const std::vector< C > &color ) {

	// Set the foreground color
	m_color = color;
}

template < typename T, typename C, uint8_t N >
inline const std::vector< C > &
designer< T, C, N >::getPenColor() const {

	// Return the current foreground color
	return m_color;
}

template < typename T, typename C, uint8_t N >
void
designer< T, C, N >::setPenPosition( T x, T y ) {

	// Update the pen position
	m_pos_x = x;
	m_pos_y = y;
}

template < typename T, typename C, uint8_t N >
inline void
designer< T, C, N >::setFont( font::base &font ) {

	// Set the text font
	m_font = &font;
}

template < typename T, typename C, uint8_t N >
inline font::base &
designer< T, C, N >::getFont() const {

	// Return the current text font
	return *m_font;
}
	
template < typename T, typename C, uint8_t N >
inline void
designer< T, C, N >::drawPoint( T x, T y ) {

	// Draw the pixel
	drawPixel( x, y, m_color.cbegin() );
}

template < typename T, typename C, uint8_t N >
void
designer< T, C, N >::drawLine( T x0, T y0, T x1, T y1 ) {

	/** === Bresenham's line algorithm === **/

	int dx = math::abs( (int) x1 - (int) x0 ),
		dy = math::abs( (int) y1 - (int) y0 );

	const bool steep = ( dy > dx );

	// Move the line to the first positive octant
	// (algorithm works only with m <= 1 and dx > dy)
	if ( steep ) {

		std::swap( x0, y0 );
		std::swap( x1, y1 );
	}

	if ( x0 > x1 ) {

		std::swap( x0, x1 );
		std::swap( y0, y1 );
	}

	// Calculate the new parameters
	dx = x1 - x0;
	dy = math::abs( (int) y1 - (int) y0 );

	// Calculate initial error and vertical step
	int e = dx / 2,
		q = ( y0 < y1 ? 1 : -1 );

	// Draw the line in the original octant
	if ( steep ) {

		drawPoint( y0, x0 );

		for ( ; x0 <= x1; ++x0, e -= dy ) {

			if ( e < 0 )
				y0 += q,e += dx;

			drawPoint( y0, x0 );
		}

	} else {

		drawPoint( x0, y0 );

		for ( ; x0 <= x1; ++x0, e -= dy ) {

			if ( e < 0 )
				y0 += q, e += dx;

			drawPoint( x0, y0 );
		}
	}
}

template < typename T, typename C, uint8_t N >
void
designer< T, C, N >::drawRect( T x0, T y0, T x1, T y1 ) {

	// Prepare the parameters
	if ( x0 > x1 )
		std::swap( x0, x1 );

	if ( y0 > y1 )
		std::swap( y0, y1 );

	// Draw the rectangle
	T i;

	for ( i = x0; i <= x1; ++i )
		drawPoint( i, y0 ), drawPoint( i, y1 );

	for ( i = y0; i <= y1; ++i )
		drawPoint( x0, i ), drawPoint( x1, i );
}

template < typename T, typename C, uint8_t N >
void
designer< T, C, N >::drawCircle( T cx, T cy, T radius ) {

	/** === Midpoint circle algorithm === **/

	int	x = 0,
		y = radius;

	int	d	= 1 - radius,
		dE	= 1,
		dSE	= -2 * radius;

	for ( ; x < y; ++x, dE += 2, d += dE ) {

		drawCirclePoints( cx, cy, x, y );

		if ( d >= 0 )
			y--, d += dSE += 2;
	}

	drawCirclePoints( cx, cy, x, y );
}

template < typename T, typename C, uint8_t N >
void
designer< T, C, N >::drawEllipse( T cx, T cy, T a, T b ) {

	/** === Midpoint ellipse algorithm === **/

	int aa = a * a, aa2 = 2 * aa,
		bb = b * b, bb2 = 2 * bb;

	int x = 0,
		y = b;

	int	dE	= 0,
		dSE	= aa2 * y,
		d	= math::round( (float) bb - (aa * b) + (0.25) * aa );


	// Draw the first region
	for ( ; dE <= dSE; ++x, dE += bb2, d += (bb + dE) ) {

		drawEllipsePoints( cx, cy, x, y );

		if ( d > 0 )
			y--, d -= dSE -= aa2;
	}

	drawEllipsePoints( cx, cy, x, y );

	// Draw the second region
	d = math::round( (float) bb * math::square( x + 0.5 ) + aa * math::square( y - 1 ) - aa * bb );

	--y;

	for ( ; y >= 0; y--, dSE -= aa2, d += (aa - dSE) ) {

		if ( d < 0 )
			++x, d += dE += bb2;

		drawEllipsePoints( cx, cy, x, y );
	}
}

template < typename T, typename C, uint8_t N >
void
designer< T, C, N >::fillRect( T x0, T y0, T x1, T y1 ) {

	// Prepare the parameters
	if ( x0 > x1 )
		std::swap( x0, x1 );

	if ( y0 > y1 )
		std::swap( y0, y1 );

	// Calculate the parameters
	int w = x1 - x0,
		h = y1 - y0;

	size_t total = (size_t) w * (size_t) h;

	// Draw the filled rectangle
	size_t i = 0;

	for ( ; i < total; ++i )
		drawPoint( (int) ( x0 + i % w ), (int) ( y0 + i / w ) );
}

template < typename T, typename C, uint8_t N >
void
designer< T, C, N >::fillCircle( T cx, T cy, T radius ) {

	/** === Midpoint circle algorithm === **/

	int	x = 0,
		y = radius;

	int	d	= 1 - radius,
		dE	= 1,
		dSE	= -2 * radius;

	for ( ; x < y; ++x, dE += 2, d += dE ) {

		drawCircleAreas( cx, cy, x, y );

		if ( d >= 0 )
			y--, d += dSE += 2;
	}

	drawCircleAreas( cx, cy, x, y );
}

template < typename T, typename C, uint8_t N >
void
designer< T, C, N >::fillEllipse( T cx, T cy, T a, T b ) {

	/** === Midpoint ellipse algorithm === **/

	int aa = a * a, aa2 = 2 * aa,
		bb = b * b, bb2 = 2 * bb;

	int x = 0,
		y = b;

	int	dE	= 0,
		dSE	= aa2 * y,
		d	= math::round( (float) bb - (aa * b) + (0.25) * aa );


	// Draw the first region
	for ( ; dE <= dSE; ++x, dE += bb2, d += (bb + dE) ) {

		drawEllipseAreas( cx, cy, x, y );

		if ( d > 0 )
			y--, d -= dSE -= aa2;
	}

	drawEllipseAreas( cx, cy, x, y );

	// Draw the second region
	d = math::round( (float) bb * math::square( x + 0.5 ) + aa * math::square( y - 1 ) - aa * bb );

	y--;

	for ( ; y >= 0; y--, dSE -= aa2, d += (aa - dSE) ) {

		if ( d < 0 )
			++x, d += dE += bb2;

		drawEllipseAreas( cx, cy, x, y );
	}
}

template < typename T, typename C, uint8_t N >
inline void
designer< T, C, N >::drawCirclePoints( T cx, T cy, T x, T y ) {

	// Draw the symmetric points of the circle
	drawPoint( cx + x, cy + y );
	drawPoint( cx - x, cy + y );
	drawPoint( cx + x, cy - y );
	drawPoint( cx - x, cy - y );

	drawPoint( cx + y, cy + x );
	drawPoint( cx - y, cy + x );
	drawPoint( cx + y, cy - x );
	drawPoint( cx - y, cy - x );
}

template < typename T, typename C, uint8_t N >
inline void
designer< T, C, N >::drawCircleAreas( T cx, T cy, T x, T y ) {

	// Draws the symmetric areas of the circle
	int i, last;

	for ( i = cx - x, last = cx + x; i <= last; ++i ) {

		drawPoint( i, cy + y );
		drawPoint( i, cy - y );
	}

	for ( i = cx - y, last = cy + y; i <= cx + y; ++i ) {

		drawPoint( i, cy + x );
		drawPoint( i, cy - x );
	}
}

template < typename T, typename C, uint8_t N >
inline void
designer< T, C, N >::drawEllipsePoints( T cx, T cy, T x, T y ) {

	// Draw the symmetric points of the ellipse
	drawPoint( cx + x, cy + y );
	drawPoint( cx - x, cy + y );
	drawPoint( cx + x, cy - y );
	drawPoint( cx - x, cy - y );
}

template < typename T, typename C, uint8_t N >
inline void
designer< T, C, N >::drawEllipseAreas( T cx, T cy, T x, T y ) {

	// Draws the symmetric areas of the ellipse
	int i, last = cx + x;

	for ( i = cx - x; i <= last; ++i ) {

		drawPoint( i, cy + y );
		drawPoint( i, cy - y );
	}
}

template < typename T, typename C, uint8_t N >
void
designer< T, C, N >::drawImage( const image::base< C > &img, T x, T y ) {

	// Check the number of channels
	if ( img.getSpectrum() != N )
		throw exception( "(Fatal) `designer->drawImage`: incorrect number of channels\n" );

	// Get the size of the image
	uint16_t	width	= img.getWidth(),
				height	= img.getHeight();

	// Iterator
	uint16_t i, j;

	// Draw the image bitmap
	for ( j = 0; j < height; ++j )
		for ( i = 0; i < width; ++i )
			drawPixel( x + i, y + j, img.getData( i, j ) );
}

template < typename T, typename C, uint8_t N >
void
designer< T, C, N >::drawChar( char32_t charcode ) {

	// Get the bitmap of the character font 
	font::glyph glyph; m_font->data( charcode, glyph );

	// Get the height of the glyph
	uint8_t height = glyph.height;

	// Pointer to a byte in the bitmap buffer
	const uint8_t *byte = glyph.buffer;

	// Calculate the real pitch and the step of the pointer
	uint8_t	pitch;
	int8_t	step;

	if ( glyph.pitch > 0 ) {

		pitch	= (uint8_t) glyph.pitch;
		step	= 1;

	} else {

		pitch	= (uint8_t) -glyph.pitch;
		step	= -1;
	}

	// Calculate the character position
	T	offx = m_pos_x,
		offy = m_pos_y + ( m_font->getHeight() - glyph.top );

	/** Monochromatic font **/

	if ( glyph.format == font::PIXEL_MODE_MONO ) {

		// Iterators
		uint8_t i, j, k;

		// Draw the character
		for ( j = 0; j < height; ++j )
			for ( i = 0; i < pitch; ++i, byte += step )
				for ( k = 0; k < 8; ++k )
					if ( *byte & ( 1 << ( 7 - k ) ) )
						drawPixel( offx + i * 8 + k, offy + j, m_color.cbegin() );
	}

	// Update the pen position
	m_pos_x += static_cast< T >( glyph.xadvance );
}

template < typename T, typename C, uint8_t N >
inline void
designer< T, C, N >::drawText( char32_t charcode ) {

	// Check if text font was loaded
	if ( !m_font )
		throw exception( "(Fatal) `designer->drawText`: no font selected\n" );

	// Draw the character
	drawChar( charcode );
}

template < typename T, typename C, uint8_t N >
inline void
designer< T, C, N >::drawText( T x, T y, char32_t charcode ) {

	// Set the pen position on the display
	setPenPosition( x, y );

	// Draw the character on the display
	drawText( charcode );
}


/* ================== Iterators ================== */

template < typename T, typename C, uint8_t N >
template < typename iterator >
void
designer< T, C, N >::drawText( iterator it, iterator end ) {

	// Check if text font was loaded
	if ( !m_font )
		throw exception( "(Fatal) `designer->drawText`: no font selected\n" );

	// Store the horizontal pen position
	T old_x = m_pos_x;

	// Draw the string
	for ( ; it != end; ++it ) {

		if ( *it != '\n' )
			drawText( (char32_t) *it );

		else {

			// Move the cursor to the new line
			m_pos_x = old_x;
			m_pos_y += m_font->getHeight();
		}
	}
}

template < typename T, typename C, uint8_t N >
template < typename iterator >
void
designer< T, C, N >::drawText( iterator it, iterator end, T width, T height, uint8_t flags ) {	

	// Check if text font was loaded
	if ( !m_font )
		throw exception( "(Fatal) `designer->drawText`: no font selected\n" );

	// Get the word wrapping mode
	bool word_break = flags & WORD_BREAK;

	// Calculate the margin factor
	T margin = 0;

	if ( flags & ALIGN_CENTER )
		margin = 2;
	else if ( flags & ALIGN_RIGHT )
		margin = 1;

	// Store the horizontal pen position
	T	old_x = m_pos_x,
		old_y = m_pos_y;

	// Start of the current line
	iterator off = it;

	// Current letter and line width
	T letter_len = 0, line_len = 0;


	// Break lines between characters
	if ( word_break ) {

		for ( ; it != end; ++it ) {

			letter_len = m_font->getWidth( *it );
			line_len += letter_len;

			if ( *it == '\n' ) {

				if ( margin )
					m_pos_x = old_x + ( width - line_len + letter_len ) / margin;

				// Draw the current line
				for ( ; off != it; ++off )
					drawChar( (char32_t) *off );

				m_pos_x = old_x;
				m_pos_y += m_font->getHeight();

				if ( ( m_pos_y - old_y ) + m_font->getHeight() > height )
					break;

				++off;
				line_len = 0;

			} else if ( line_len > width ) {

				if ( margin )
					m_pos_x = ( width - line_len + letter_len ) / margin;

				// Draw the current line
				for ( ; off != it; ++off )
					drawChar( (char32_t) *off );

				m_pos_x = old_x;
				m_pos_y += m_font->getHeight();

				if ( ( m_pos_y - old_y ) + m_font->getHeight() > height )
					break;

				line_len = letter_len;
			}
		}

		if ( it == end ) {

			if ( margin )
				m_pos_x = old_x + ( width - line_len ) / margin;

			// Append the last line
			for ( ; off != end; ++off )
				drawChar( (char32_t) *off );
		}


	// Break lines between words, except when a single word is longer than the width
	} else {

		// Start of the current word
		iterator word_start = it;

		// Current word width
		T word_len = 0;

		// Space character length
		T space_len = m_font->getWidth( ' ' );

		for ( ; it != end; ++it ) {

			letter_len = m_font->getWidth( *it );
			word_len += letter_len;

			if ( line_len + word_len > width ) {

				if ( off == word_start ) {

					if ( margin )
						m_pos_x = old_x + ( width - ( line_len + word_len ) + space_len ) / margin;

					// Draw the current line
					for ( ; off != it; ++off )
						drawChar( (char32_t) *off );

					m_pos_x = old_x;
					m_pos_y += m_font->getHeight();

					word_start = it;
					line_len = 0;
					word_len = space_len;

				} else {

					if ( margin )
						m_pos_x = old_x + ( width - line_len + space_len ) / margin;

					// Draw the current line
					for ( ; off != word_start; ++off )
						drawChar( (char32_t) *off );

					m_pos_x = old_x;
					m_pos_y += m_font->getHeight();

					off = ++word_start;
					line_len = 0;
				}

				if ( ( m_pos_y - old_y ) + m_font->getHeight() > height )
					break;
			}

			if ( *it == '\n' ) {

				if ( margin )
					m_pos_x = old_x + ( width - ( line_len + word_len ) + space_len ) / margin;

				// Draw the current line
				for ( ; off != it; ++off )
					drawChar( (char32_t) *off );

				m_pos_x = old_x;
				m_pos_y += m_font->getHeight();

				if ( ( m_pos_y - old_y ) + m_font->getHeight() > height )
					break;

				off = word_start = it + 1;
				line_len = word_len = 0;

			} else if ( *it == ' ' ) {

				word_start = it;

				line_len += word_len;
				word_len = 0;
			}
		}

		if ( it == end ) {

			if ( margin )
				m_pos_x = old_x + ( width - ( line_len + word_len ) ) / margin;

			// Append the last line
			for ( ; off != end; ++off )
				drawChar( (char32_t) *off );
		}
	}
}

template < typename T, typename C, uint8_t N >
template < typename iterator >
inline void
designer< T, C, N >::drawText( T x, T y, iterator it, iterator end ) {

	// Set the pen position
	setPenPosition( x, y );

	// Draw the string
	drawText( it, end );
}

template < typename T, typename C, uint8_t N >
template < typename iterator >
inline void
designer< T, C, N >::drawText( T x, T y, iterator it, iterator end, T width, T height, uint8_t flags ) {

	// Set the pen position
	setPenPosition( x, y );

	// Draw the multiline string
	drawText( it, end, width, height, flags );
}


/* ================== Strings ================== */

template < typename T, typename C, uint8_t N >
inline void
designer< T, C, N >::drawText( const std::string &text ) {

	// Draw the string
	drawText( text.begin(), text.end() );
}

template < typename T, typename C, uint8_t N >
inline void
designer< T, C, N >::drawText( const std::string &text, T width, T height, uint8_t flags ) {

	// Draw the multiline string
	drawText( text.begin(), text.end(), width, height, flags );
}

template < typename T, typename C, uint8_t N >
inline void
designer< T, C, N >::drawText( T x, T y, const std::string &text ) {

	// Draw the string
	drawText( x, y, text.begin(), text.end() );
}

template < typename T, typename C, uint8_t N >
inline void
designer< T, C, N >::drawText( T x, T y, const std::string &text, T width, T height, uint8_t flags ) {

	// Draw the multiline string
	drawText( x, y, text.begin(), text.end(), width, height, flags );
}


/* ================== Unicode strings ================== */

template < typename T, typename C, uint8_t N >
inline void
designer< T, C, N >::drawText( const std::u32string &text ) {

	// Draws the unicode string
	drawText( text.begin(), text.end() );
}

template < typename T, typename C, uint8_t N >
inline void
designer< T, C, N >::drawText( const std::u32string &text, T width, T height, uint8_t flags ) {

	// Draw the multiline unicode string
	drawText( text.begin(), text.end(), width, height, flags );
}

template < typename T, typename C, uint8_t N >
inline void
designer< T, C, N >::drawText( T x, T y, const std::u32string &text ) {

	// Set the pen position
	setPenPosition( x, y );

	// Draw the unicode string
	drawText( text.begin(), text.end() );
}

template < typename T, typename C, uint8_t N >
inline void
designer< T, C, N >::drawText( T x, T y, const std::u32string &text, T width, T height, uint8_t flags ) {

	// Draw the multiline unicode string
	drawText( x, y, text.begin(), text.end(), width, height, flags );
}

} // End of main namespace

#endif /* _RPI_HW_DESIGNER_INL_HPP_ */
