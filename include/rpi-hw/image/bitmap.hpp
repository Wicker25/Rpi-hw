/* 
    Title --- bitmap.hpp

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


#ifndef _RPI_HW_IMAGE_BITMAP_HPP_
#define _RPI_HW_IMAGE_BITMAP_HPP_

#include <memory>
#include <algorithm>
#include <vector>

#if USE_MAGICK
#include <Magick++.h>
#endif

#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>

#include <rpi-hw/utils.hpp>
#include <rpi-hw/utils-inl.hpp>

#include <rpi-hw/image/base.hpp>

namespace rpihw { // Begin main namespace

namespace image { // Begin images namespace

#if USE_MAGICK

	//! Hack to initialize the Magick++ API.
	struct InitMagick {

		InitMagick() { Magick::InitializeMagick( NULL ); }
	};

	//! Magick++ initializer.
	static InitMagick magick;

#endif


/*!
	@class bitmap
	@brief Bitmap image.
*/
template < typename T >
class bitmap : public image::base< T > {

public:

	/*!
		@brief Constructor method.
		@param[in] width The width of the image.
		@param[in] height The height of the image.
		@param[in] channels Number of color channel.
	*/
	bitmap( uint16_t width, uint16_t height, uint8_t channels );


#if USE_MAGICK

	/*!
		@brief Constructor method.
		@param[in] path The path to the image file.
	*/
	bitmap( const std::string &path );

	/*!
		@brief Constructor method.
		@param[in] img An Magick::Image object.
	*/
	bitmap( Magick::Image &img );

#endif /* USE_MAGICK */


	//! Destructor method.
	virtual ~bitmap();

	//! Returns the width of the image.
	virtual uint16_t getWidth() const;

	//! Returns the height of the image.
	virtual uint16_t getHeight() const;

	//! Returns the number of image channels.
	virtual uint8_t getSpectrum() const;

	/*!
		@brief Sets the color of a pixel.
		@param[in] x The horizontal position of the pixel.
		@param[in] y The vertical position of the pixel.
		@param[in] color A pointer to the color data.
	*/
	void setData( uint16_t x, uint16_t y, T *color );

	/*!
		@brief Sets the channel value of a pixel.
		@param[in] x The horizontal position of the pixel.
		@param[in] y The vertical position of the pixel.
		@param[in] c The color channel.
		@param[in] value The channel value of the pixel.
	*/
	void setData( uint16_t x, uint16_t y, uint8_t c, T value );

	/*!
		@brief Returns the color of a pixel.
		@param[in] x The horizontal position of the pixel.
		@param[in] y The vertical position of the pixel.
		@return An iterator to the color data.
	*/
	virtual color_iterator< T > getData( uint16_t x, uint16_t y ) const;

	/*!
		@brief Returns the channel value of a pixel.
		@param[in] x The horizontal position of the pixel.
		@param[in] y The vertical position of the pixel.
		@param[in] c The color channel.
		@return The channel value of the pixel.
	*/
	virtual T getData( uint16_t x, uint16_t y, uint8_t c ) const;

protected:

	//@{
	//! Size of the bitmap.
	uint32_t m_width, m_height;
	//@}

	//! Number of color channel.
	uint8_t m_channels;

	//! The data buffer.
	std::vector< T > m_buffer;

#if USE_MAGICK

	/*!
		@brief Converts Magick::Image object to the bitmap buffer.
		@param[in] img An Magick::Image object.
	*/
	void loadMagickObj( Magick::Image &img );

#endif
};

} // End of images namespace

} // End of main namespace


// Include inline methods 
#include <rpi-hw/image/bitmap-inl.hpp>

#endif /* _RPI_HW_IMAGE_BITMAP_HPP_ */
