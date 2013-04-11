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

template < typename T, typename Color >
designer< T, Color >::designer( T width, T height ) {

	// Store the the size of the drawing area
	m_area.w = width;
	m_area.h = height;


	// FIXME FIXME FIXME FIXME FIXME
	// FIXME FIXME FIXME FIXME FIXME

	// Set the text font
	m_font = new font::freetype( "font.ttf", 8, font::RENDER_MONOCHROME );


	// Set the initial cursor position
	move( 0, 0 );
}

template < typename T, typename Color >
designer< T, Color >::~designer() {

}

template < typename T, typename Color >
inline void
designer< T, Color >::setColor( Color color ) {

	// Set the foreground color
	m_color = color;
}

template < typename T, typename Color >
inline Color
designer< T, Color >::getColor() const {

	// Return the current foreground color
	return m_color;
}

template < typename T, typename Color >
inline void
designer< T, Color >::setPixel( T x, T y ) {

	// Set the color of the pixel
	setPixel( x, y, m_color );
}

template < typename T, typename Color >
void
designer< T, Color >::drawLine( T x0, T y0, T x1, T y1 ) {

	/** === Bresenham's line algorithm === **/

	int dx = math::abs( (int) x1 - (int) x0 ),
		dy = math::abs( (int) y1 - (int) y0 );

	const bool steep = ( dy > dx );

	// Move the line to the first positive octant
	// (algorithm works only with m <= 1 and dx > dy)
	if ( steep ) {

		utils::swap( x0, y0 );
		utils::swap( x1, y1 );
	}

	if ( x0 > x1 ) {

		utils::swap( x0, x1 );
		utils::swap( y0, y1 );
	}

	// Calculate the new parameters
	dx = x1 - x0;
	dy = math::abs( (int) y1 - (int) y0 );

	// Calculate initial error and vertical step
	int e = dx / 2,
		q = ( y0 < y1 ? 1 : -1 );

	// Draw the line in the original octant
	if ( steep ) {

		setPixel( y0, x0 );

		for ( ; x0 <= x1; x0++, e -= dy ) {

			if ( e < 0 )
				y0 += q,e += dx;

			setPixel( y0, x0 );
		}

	} else {

		setPixel( x0, y0 );

		for ( ; x0 <= x1; x0++, e -= dy ) {

			if ( e < 0 )
				y0 += q, e += dx;

			setPixel( x0, y0 );
		}
	}
}

template < typename T, typename Color >
void
designer< T, Color >::drawRect( T x0, T y0, T x1, T y1 ) {

	// Prepare the parameters
	if ( x0 > x1 )
		utils::swap( x0, x1 );

	if ( y0 > y1 )
		utils::swap( y0, y1 );

	// Draw the rectangle
	T i;

	for ( i = x0; i <= x1; i++ )
		setPixel( i, y0 ), setPixel( i, y1 );

	for ( i = y0; i <= y1; i++ )
		setPixel( x0, i ), setPixel( x1, i );
}

template < typename T, typename Color >
void
designer< T, Color >::drawCircle( T cx, T cy, T radius ) {

	/** === Midpoint circle algorithm === **/

	int	x = 0,
		y = radius;

	int	d	= 1 - radius,
		dE	= 1,
		dSE	= -2 * radius;

	for ( ; x < y; x++, dE += 2, d += dE ) {

		drawCirclePoints( cx, cy, x, y );

		if ( d >= 0 )
			y--, d += dSE += 2;
	}

	drawCirclePoints( cx, cy, x, y );
}

template < typename T, typename Color >
void
designer< T, Color >::drawEllipse( T cx, T cy, T a, T b ) {

	/** === Midpoint ellipse algorithm === **/

	int aa = a * a, aa2 = 2 * aa,
		bb = b * b, bb2 = 2 * bb;

	int x = 0,
		y = b;

	int	dE	= 0,
		dSE	= aa2 * y,
		d	= math::round( (float) bb - (aa * b) + (0.25) * aa );


	// Draw the first region
	for ( ; dE <= dSE; x++, dE += bb2, d += (bb + dE) ) {

		drawEllipsePoints( cx, cy, x, y );

		if ( d > 0 )
			y--, d -= dSE -= aa2;
	}

	drawEllipsePoints( cx, cy, x, y );

	// Draw the second region
	d = math::round( (float) bb * math::square( x + 0.5 ) + aa * math::square( y - 1 ) - aa * bb );

	y--;

	for ( ; y >= 0; y--, dSE -= aa2, d += (aa - dSE) ) {

		if ( d < 0 )
			x++, d += dE += bb2;

		drawEllipsePoints( cx, cy, x, y );
	}
}

template < typename T, typename Color >
void
designer< T, Color >::fillRect( T x0, T y0, T x1, T y1 ) {

	// Prepare the parameters
	if ( x0 > x1 )
		utils::swap( x0, x1 );

	if ( y0 > y1 )
		utils::swap( y0, y1 );

	// Calculate the parameters
	int w = x1 - x0,
		h = y1 - y0;

	size_t total = (size_t) w * (size_t) h;

	// Draw the filled rectangle
	size_t i = 0;

	for ( ; i < total; i++ )
		setPixel( (int) ( x0 + i % w ), (int) ( y0 + i / w ) );
}

template < typename T, typename Color >
void
designer< T, Color >::fillCircle( T cx, T cy, T radius ) {

	/** === Midpoint circle algorithm === **/

	int	x = 0,
		y = radius;

	int	d	= 1 - radius,
		dE	= 1,
		dSE	= -2 * radius;

	for ( ; x < y; x++, dE += 2, d += dE ) {

		drawCircleAreas( cx, cy, x, y );

		if ( d >= 0 )
			y--, d += dSE += 2;
	}

	drawCircleAreas( cx, cy, x, y );
}

template < typename T, typename Color >
void
designer< T, Color >::fillEllipse( T cx, T cy, T a, T b ) {

	/** === Midpoint ellipse algorithm === **/

	int aa = a * a, aa2 = 2 * aa,
		bb = b * b, bb2 = 2 * bb;

	int x = 0,
		y = b;

	int	dE	= 0,
		dSE	= aa2 * y,
		d	= math::round( (float) bb - (aa * b) + (0.25) * aa );


	// Draw the first region
	for ( ; dE <= dSE; x++, dE += bb2, d += (bb + dE) ) {

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
			x++, d += dE += bb2;

		drawEllipseAreas( cx, cy, x, y );
	}
}

template < typename T, typename Color >
inline void
designer< T, Color >::drawCirclePoints( T cx, T cy, T x, T y ) {

	// Draw the symmetric points of the circle
	setPixel( cx + x, cy + y );
	setPixel( cx - x, cy + y );
	setPixel( cx + x, cy - y );
	setPixel( cx - x, cy - y );

	setPixel( cx + y, cy + x );
	setPixel( cx - y, cy + x );
	setPixel( cx + y, cy - x );
	setPixel( cx - y, cy - x );
}

template < typename T, typename Color >
inline void
designer< T, Color >::drawCircleAreas( T cx, T cy, T x, T y ) {

	// Draws the symmetric areas of the circle
	int i, last;

	for ( i = cx - x, last = cx + x; i < last; i++ ) {

		setPixel( i, cy + y );
		setPixel( i, cy - y );
	}

	for ( i = cx - y, last = cy + y; i < cx + y; i++ ) {

		setPixel( i, cy + x );
		setPixel( i, cy - x );
	}
}

template < typename T, typename Color >
inline void
designer< T, Color >::drawEllipsePoints( T cx, T cy, T x, T y ) {

	// Draw the symmetric points of the ellipse
	setPixel( cx + x, cy + y );
	setPixel( cx - x, cy + y );
	setPixel( cx + x, cy - y );
	setPixel( cx - x, cy - y );
}

template < typename T, typename Color >
inline void
designer< T, Color >::drawEllipseAreas( T cx, T cy, T x, T y ) {

	// Draws the symmetric areas of the ellipse
	int i, last = cx + x;

	for ( i = cx - x; i <= last; i++ ) {

		setPixel( i, cy + y );
		setPixel( i, cy - y );
	}
}

template < typename T, typename Color >
void
designer< T, Color >::drawBitmap( const bitmap &img, T x, T y ) {

	/*
	// Get the width of the image
	size_t width = img.width();

	// Calculate the number of the pixels
	size_t size = width * img.height();

	// The position of the current pixel
	T offx, offy;

	// Iterator
	size_t i = 0;

	// Draw the image bitmap
	for ( ; i < size; i++ ) {

		offx = (T) ( i % width );
		offy = (T) ( i / width );

		setPixel( x + offx, y + offy, *img.data( offx, offy, 0 ) );
	}
	*/
}

template < typename T, typename Color >
inline bool
designer< T, Color >::isLineFull( uint8_t charcode ) { // FIXME FIXME FIXME

	// Check if the current line is full
	return ( m_pos.x + m_font->getWidth( charcode ) >= m_area.w );
}

template < typename T, typename Color >
void
designer< T, Color >::newLine() { // FIXME FIXME FIXME

	// Move the cursor to the new line
	m_pos.x = 0;
	m_pos.y += m_font->getHeight();
}

template < typename T, typename Color >
void
designer< T, Color >::move( T x, T y ) {

	// Check if position exists
	if ( x < 0 || y < 0 || x >= m_area.w || y >= m_area.h )
		throw exception( utils::format( "(Error) `designer->move`: the position (%u,%u) does not exists\n", x, y ) );

	// Update the cursor position
	m_pos.x = x;
	m_pos.y = y;
}

template < typename T, typename Color >
void
designer< T, Color >::write( uint8_t charcode ) {

	// Check if there are no still spaces available in the row
	if ( isLineFull( charcode ) )
		newLine();

	// Get the bitmap of the character font 
	font::glyph glyph;

	m_font->data( charcode, glyph );

	// FIXME FIXME FIXME FIXME FIXME Negative `data.pitch`!!!!

	// Current byte
	uint8_t byte;

	// Calculate the offset position of the character
	size_t offx = m_pos.x;
	size_t offy = m_pos.y + ( m_font->getHeight() - glyph.top );

	// Number of bytes of the bitmap
	size_t nbytes = glyph.pitch * glyph.height;

	// Iterators
	size_t n, i, j, k;

	for ( n = 0; n < nbytes; n++ ) {

		i = n % glyph.pitch;
		j = n / glyph.pitch;

		byte = glyph.buffer[ n ];

		for ( k = 0; k < 8; k++ ) {

			if ( byte & ( 1 << ( 7 - k ) ) )
				setPixel( offx + i * 8 + k, offy + j );	// ( data.height - j )	FIXME FIXME FIXME
		}
	}

	// Update the cursor position
	m_pos.x += glyph.xadvance;
}

template < typename T, typename Color >
void
designer< T, Color >::write( T x, T y, uint8_t charcode ) {

	// Set the position of the cursor on the display
	move( x, y );

	// Write the character on the display
	write( charcode );
}

template < typename T, typename Color >
void
designer< T, Color >::write( const std::string &text ) {

	// Draw the text
	size_t i = 0;

	for ( ; i < text.size(); i++ ) {

		if ( text[i] != '\n' )
			write( (uint8_t) text[i] );
		else
			newLine();
	}
}

template < typename T, typename Color >
void
designer< T, Color >::write( const std::string &text, T width, T height, TextAlign align ) {

	size_t i = 0;

	for ( ; i < text.size(); i++ ) {

		if ( text[i] == ' ' ) {

			
		}
	}

	/*
		std::cout << text.substr( off, len ) << std::endl;
		write( text.substr( off, len ) );
		newLine();
	*/






	/*
	// The aligned text
	std::string al = text;

	// Line length and number of spaces to insert at the start of line
	size_t len, spaces;

	// Start of the new line and position of the last white space
	size_t off = 0, last = 0;

	// Iterator
	size_t i = 0;

	// Align the text
	for ( ; i < al.length(); i++ ) {

		// Calculate the length of the line at current position
		len = i - off;

		// Check if the line has reached the maximum width
		if ( len >= width ) {

			// Break lines between words, except when a single word is longer than the width
			if ( !truncate && last != off ) {

				al.erase( al.begin() + last );
				i = last;
			}

			// Insert the new line character and update the offsets
			al.insert( al.begin() + i, '\n' );
			off = i + 1;

		// Split the line according to the new line character
		} else if ( al[i] == '\n' ) {

			// Update the offsets
			last = off = i + 1;

		// Store the last white space
		} else if ( al[i] == ' ' ) last = i;
	}
	*/
}

template < typename T, typename Color >
void
designer< T, Color >::write( T x, T y, const std::string &text ) {

	// Set the position of the cursor on the display
	move( x, y );

	// Write the string on the display
	write( text );
}

} // End of main namespace

#endif
