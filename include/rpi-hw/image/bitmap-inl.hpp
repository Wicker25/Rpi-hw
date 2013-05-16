/* 
    Title --- bitmap-inl.hpp

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


#ifndef _RPI_HW_IMAGE_BITMAP_INL_HPP_
#define _RPI_HW_IMAGE_BITMAP_INL_HPP_

namespace rpihw { // Begin main namespace

namespace image { // Begin images namespace

template < typename T >
bitmap< T >::bitmap( uint16_t width, uint16_t height, uint8_t channels ) 

	: m_width		( width )
	, m_height		( height )
	, m_channels	( channels )
	, m_buffer		( width * height * channels, 0 ) {

}


#if USE_MAGICK

template < typename T >
bitmap< T >::bitmap( const std::string &path ) {

	// Load the image using Magick++ API
	Magick::Image img( path );

	// Convert the Magick::Image object to the bitmap buffer
	loadMagickObj( img );
}

template < typename T >
bitmap< T >::bitmap( Magick::Image &img ) {

	// Convert the Magick::Image object to the bitmap buffer
	loadMagickObj( img );
}

template < typename T >
void
bitmap< T >::loadMagickObj( Magick::Image &img ) {

	// Copy the image data
	m_width		= (uint16_t)	img.columns();
	m_height	= (uint16_t)	img.rows();

	// Get the pixels of the image
	const Magick::PixelPacket *pixels = img.getConstPixels( 0, 0, m_width, m_height );

	// Size of the bitmap buffer (incomplete)
	size_t size = m_width * m_height;

	// Iterator
	size_t i;

	// Convert Magick::Image object to the bitmap buffer
	switch ( img.type() ) {

		case Magick::PaletteMatteType:
		case Magick::TrueColorMatteType:
		case Magick::ColorSeparationType: {

			// Set the number of image channels
			m_channels = 4;

			// Allocate the bitmap buffer
			m_buffer.resize( size * m_channels );

			// Iterator of the bitmap buffer
			auto it = m_buffer.begin();

			for ( i = 0; i < size; ++i, ++pixels ) {

				*it++ = (T) pixels->red;
				*it++ = (T) pixels->green;
				*it++ = (T) pixels->blue;
				*it++ = (T) pixels->opacity;
			}

			break;
		}

		case Magick::PaletteType:
		case Magick::TrueColorType: {

			// Set the number of image channels
			m_channels = 3;

			// Allocate the bitmap buffer
			m_buffer.resize( size * m_channels );

			// Iterator of the bitmap buffer
			auto it = m_buffer.begin();

			for ( i = 0; i < size; ++i, ++pixels ) {

				*it++ = (T) pixels->red;
				*it++ = (T) pixels->green;
				*it++ = (T) pixels->blue;
			}

			break;
		}

		case Magick::GrayscaleMatteType: {

			// Set the number of image channels
			m_channels = 2;

			// Allocate the bitmap buffer
			m_buffer.resize( size * m_channels );

			// Iterator of the bitmap buffer
			auto it = m_buffer.begin();

			for ( i = 0; i < size; ++i, ++pixels ) {

				*it++ = (T) pixels->red;
				*it++ = (T) pixels->opacity;
			}

			break;
		}

		default: {

			// Set the number of image channels
			m_channels = 1;

			// Allocate the bitmap buffer
			m_buffer.resize( size * m_channels );

			// Iterator of the bitmap buffer
			auto it = m_buffer.begin();

			for ( i = 0; i < size; ++i, ++pixels )
				*it++ = (T) pixels->red;

			break;
		}
	}
}

#endif /* USE_MAGICK */


template < typename T >
bitmap< T >::~bitmap() {

}

template < typename T >
inline uint16_t
bitmap< T >::getWidth() const {

	// Return the width of the image
	return m_width;
}

template < typename T >
inline uint16_t
bitmap< T >::getHeight() const {

	// Return the height of the image
	return m_height;
}

template < typename T >
inline uint8_t
bitmap< T >::getSpectrum() const {

	// Return the number of image channels
	return m_channels;
}

template < typename T >
inline void
bitmap< T >::setData( uint16_t x, uint16_t y, T *color ) {

	// Set the color of the pixel
	std::copy( color, color +  m_channels, m_buffer + (size_t) m_channels * ( (size_t) x + (size_t) y * (size_t) m_width ) );
}

template < typename T >
inline void
bitmap< T >::setData( uint16_t x, uint16_t y, uint8_t c, T value ) {

	// Set the channel value of the pixel
	m_buffer[ (size_t) m_channels * ( (size_t) x + (size_t) y * (size_t) m_width ) + c ] = value;
}

template < typename T >
inline color_iterator< T >
bitmap< T >::getData( uint16_t x, uint16_t y ) const {

	// Return the color data into the buffer
	return m_buffer.begin() + (size_t) m_channels * ( (size_t) x + (size_t) y * (size_t) m_width );
}

template < typename T >
inline T
bitmap< T >::getData( uint16_t x, uint16_t y, uint8_t c ) const {

	// Return the channel value of the pixel
	return *( getData( x, y ) + c );
}

} // End of images namespace

} // End of main namespace

#endif /* _RPI_HW_IMAGE_BITMAP_INL_HPP_ */
