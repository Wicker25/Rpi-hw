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
		@brief Constructor method.
		@param[in] name The name of the font.
		@param[in] height The height of the font.
	*/
	base( const std::string &name, uint8_t height );

	//! Destructor method.
	virtual ~base();

	/*!
		@brief Returns the width of a character.
		@param[in] charcode The character code.
	*/
	virtual uint8_t getWidth( uint32_t charcode ) const = 0;

	//! Returns the height of the font.
	virtual uint8_t getHeight() const;

	/*!
		@brief Returns the data of the character font.
		@param[in] charcode The character code.
		@return glyph_data The glyph of the character.
	*/
	virtual void data( uint32_t charcode, glyph &glyph ) const = 0;

protected:

	//! Name of the font.
	std::string m_name;

	//! Font height.
	uint8_t m_height;
};

} // End of fonts namespace

} // End of main namespace

#endif
