/* 
    Title --- image/base.hpp

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


#ifndef _RPI_HW_IMAGE_BASE_HPP_
#define _RPI_HW_IMAGE_BASE_HPP_

#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>

namespace rpihw { // Begin main namespace

/*!
	@namespace rpihw::image
	@brief Namespace of the fonts.
*/

namespace image { // Begin images namespace

/*!
	@class base
	@brief Generic image.
*/
template < typename T >
class base {

public:

	//! Returns the width of the image.
	virtual uint16_t getWidth() const = 0;

	//! Returns the height of the image.
	virtual uint16_t getHeight() const = 0;

	//! Returns the number of image channels.
	virtual uint8_t getSpectrum() const = 0;

	/*!
		@brief Returns the color of a pixel.
		@param[in] x The horizontal position of the pixel.
		@param[in] y The vertical position of the pixel.
		@return A pointer to the color data.
	*/
	virtual const T *getData( uint16_t x, uint16_t y ) const = 0;

	/*!
		@brief Returns the channel value of a pixel.
		@param[in] x The horizontal position of the pixel.
		@param[in] y The vertical position of the pixel.
		@param[in] c The color channel.
		@return The channel value of the pixel.
	*/
	virtual T getData( uint16_t x, uint16_t y, uint8_t c ) const = 0;
};

} // End of images namespace

} // End of main namespace

#endif /* _RPI_HW_IMAGE_BASE_HPP_ */
