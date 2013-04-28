/* 
    Title --- font/freetype-inl.hpp

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


#include <rpi-hw/config.hpp>

#if USE_FREETYPE

#ifndef _RPI_HW_FONT_FREETYPE_INL_HPP_
#define _RPI_HW_FONT_FREETYPE_INL_HPP_

namespace rpihw { // Begin main namespace

namespace font { // Begin fonts namespace

inline const std::string &
freetype::getPath() const {

	// Return the path to the font
	return m_path;
}

inline void
freetype::setSize( uint8_t height ) {

	// Set the font size
	m_image_type->width		= height;
	m_image_type->height	= height;
}

inline uint8_t
freetype::getHeight() const {

	// Return the height of the font
	return m_image_type->height;
}

} // End of fonts namespace

} // End of main namespace

#endif /* _RPI_HW_FONT_FREETYPE_INL_HPP_ */

#endif /* USE_FREETYPE */
