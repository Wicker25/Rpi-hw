/* 
    Title --- font/base.hpp

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


#ifndef _RPI_HW_FONT_BASE_HPP_
#define _RPI_HW_FONT_BASE_HPP_

#include <iostream>

#include <rpi-hw/types.hpp>
#include <rpi-hw/font/glyph.hpp>

namespace rpihw { // Begin main namespace

/*!
	@namespace rpihw::font
	@brief Namespace of the fonts.
*/

namespace font { // Begin fonts namespace

//! The font rendering mode.
enum RenderMode {

	RENDER_DEFAULT		= 0,
	RENDER_MONOCHROME	= 1
};

/*!
	@class base
	@brief Generic font.
*/
class base {

public:

	/*!
		@brief Sets the font size.
		@param[in] height The height of the font.
	*/
	virtual void setSize( uint8_t height ) = 0;

	/*!
		@brief Returns the width of a character.
		@param[in] charcode The character code.
		@return The width of the font.
	*/
	virtual uint8_t getWidth( uint32_t charcode ) const = 0;

	//! Returns the height of the font.
	virtual uint8_t getHeight() const = 0;

	/*!
		@brief Returns the data of the character font.
		@param[in] charcode The character code.
		@param[in] glyph The glyph of the character.
	*/
	virtual void data( uint32_t charcode, glyph &glyph ) const = 0;
};

} // End of fonts namespace

} // End of main namespace

#endif /* _RPI_HW_FONT_BASE_HPP_ */
