/* 
    Title --- bitmap.hpp [work in progress]

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


#ifndef _RPI_HW_BITMAP_HPP_
#define _RPI_HW_BITMAP_HPP_

// Include the CImg library
// #define cimg_display 0
// #include <CImg.h>

#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>

// Using the CImg's namespace
//using namespace cimg_library;

namespace rpihw { // Begin main namespace

/*!
	@class bitmap
	@brief Simple bitmap structure.
*/
class bitmap {

public:

	/*!
		@brief Constructor method.
		@param[in] size Number of the bits.
		@param[in] value Default value of the bits.
	*/
	bitmap( size_t width, size_t height, uint8_t *data );

	//! Destructor method.
	virtual ~bitmap();

	/*!
		@brief Sets the color of a pixel.
		@param[in] x The horizontal position of the pixel.
		@param[in] y The vertical position of the pixel.
		@param[in] channel The color channel.
	*/
	template < typename T >
	T data( size_t x, size_t y, size_t channel = 0 ) const;

private:

	//! Width of the image.
	size_t m_width;

	//! Height of the image.
	size_t m_height;

	//! Number of color channel.
	uint8_t m_channels;

	//! Data of the image.
	uint8_t *m_data;
};

} // End of main namespace

#endif
