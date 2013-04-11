/* 
    Title --- font/freetype.hpp

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


#ifndef _RPI_HW_FONT_FREETYPE_HPP_
#define _RPI_HW_FONT_FREETYPE_HPP_

#include <string>

// FreeType Headers
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_CACHE_H
#include FT_CACHE_CHARMAP_H
#include FT_CACHE_SMALL_BITMAPS_H

#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>

#include <rpi-hw/font/base.hpp>

namespace rpihw { // Begin main namespace

namespace font { // Begin fonts namespace

//! Function used by `FTC_Manager_New` to call the method `freetype::buildFace`.
FT_Error faceRequester( FTC_FaceID face_id, FT_Library library, FT_Pointer obj, FT_Face *face );

/*!
	@class freetype
	@brief True Type Font.
*/
class freetype : public font::base {

public:

	/*!
		@brief Constructor method.
		@param[in] name The name of the font.
		@param[in] height The height of the font.
		@param[in] mode The fond rendering mode.
	*/
	freetype( const std::string &name, uint8_t height, RenderMode mode = font::RENDER_DEFAULT );

	//! Destructor method.
	virtual ~freetype();

	/*!
		@brief Returns the width of a character.
		@param[in] charcode The character code.
	*/
	virtual uint8_t getWidth( uint32_t charcode ) const;

	/*!
		@brief Returns the data of the character font.
		@param[in] charcode The character code.
		@return glyph_data The glyph of the character.
	*/
	virtual void data( uint32_t charcode, glyph &glyph ) const;

	//! Builds the fresh new font object (don't use directly).
	void buildFace( FTC_FaceID face_id, FT_Face *face );

protected:

	//! The FreeType library instance.
	FT_Library m_library;

	//! The cache manager.
	FTC_Manager m_manager;

	//! Type of images in the glyph cache.
	FTC_ImageType m_image_type;

	//! Charmap cache.
	FTC_CMapCache m_cmap_cache;

	//! Small bitmap cache.
	FTC_SBitCache m_sbit_cache;

	/*!
		@brief Gets the bitmap of the character.
		@param[in] charcode The character code.
		@param[out] sbit The handle to the bitmap.
	*/
	void getSBitChar( uint32_t charcode, FTC_SBit &sbit ) const;
};

} // End of fonts namespace

} // End of main namespace

#endif
