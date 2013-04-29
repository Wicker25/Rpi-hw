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


#include <rpi-hw/config.hpp>

#if USE_FREETYPE

#ifndef _RPI_HW_FONT_FREETYPE_HPP_
#define _RPI_HW_FONT_FREETYPE_HPP_

#include <iostream>
#include <string>

// FreeType Headers
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_CACHE_H
#include FT_CACHE_CHARMAP_H
#include FT_CACHE_SMALL_BITMAPS_H

#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>
#include <rpi-hw/math.hpp>

#include <rpi-hw/font/base.hpp>

namespace rpihw { // Begin main namespace

namespace font { // Begin fonts namespace

//! The character sets supported by charmaps.
enum Encoding {

	ENCODING_NONE				= FT_ENCODING_NONE,
	ENCODING_UNICODE			= FT_ENCODING_UNICODE,
	ENCODING_MS_SYMBOL			= FT_ENCODING_MS_SYMBOL,
	ENCODING_SJIS				= FT_ENCODING_SJIS,
	ENCODING_GB2312				= FT_ENCODING_GB2312,
	ENCODING_BIG5				= FT_ENCODING_BIG5,
	ENCODING_WANSUNG			= FT_ENCODING_WANSUNG,
	ENCODING_JOHAB				= FT_ENCODING_JOHAB,
	ENCODING_ADOBE_LATIN_1		= FT_ENCODING_ADOBE_LATIN_1,
	ENCODING_ADOBE_STANDARD		= FT_ENCODING_ADOBE_STANDARD,
	ENCODING_ADOBE_EXPERT		= FT_ENCODING_ADOBE_EXPERT,
	ENCODING_ADOBE_CUSTOM		= FT_ENCODING_ADOBE_CUSTOM,
	ENCODING_APPLE_ROMAN		= FT_ENCODING_APPLE_ROMAN
};

//! Function used by `FTC_Manager_New` to call the method `freetype::buildFace`.
FT_Error faceRequester( FTC_FaceID face_id, FT_Library library, FT_Pointer obj, FT_Face *face );

/*!
	@class freetype
	@brief TrueType font.
*/
class freetype : public font::base {

public:

	/*!
		@brief Constructor method.
		@param[in] path The path to the font.
		@param[in] height The height of the font.
		@param[in] mode The fond rendering mode.
		@param[in] encoding The character set used by the font.
	*/
	freetype( const std::string &path, uint8_t height, RenderMode mode = font::RENDER_DEFAULT, Encoding encoding = ENCODING_NONE );

	//! Destructor method.
	virtual ~freetype();

	//! Returns the path to the font.
	virtual const std::string &getPath() const;

	/*!
		@brief Sets the font size.
		@param[in] height The height of the font.
	*/
	virtual void setSize( uint8_t height );

	/*!
		@brief Returns the width of a character.
		@param[in] charcode The character code.
	*/
	virtual uint8_t getWidth( uint32_t charcode ) const;

	//! Returns the height of the font.
	virtual uint8_t getHeight() const;

	/*!
		@brief Returns the data of the character font.
		@param[in] charcode The character code.
		@param[out] glyph The glyph of the character.
	*/
	virtual void data( uint32_t charcode, glyph &glyph ) const;

	//! Builds the fresh new font object (don't use directly).
	void buildFace( FTC_FaceID face_id, FT_Face *face );

protected:

	//! Path to the font.
	std::string m_path;

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

	//! The character set used by the font.
	Encoding m_encoding;

	/*!
		@brief Gets the bitmap of the character.
		@param[in] charcode The character code.
		@param[out] sbit The handle to the bitmap.
	*/
	void getSBitChar( uint32_t charcode, FTC_SBit &sbit ) const;
};

} // End of fonts namespace

} // End of main namespace

#endif /* _RPI_HW_FONT_FREETYPE_HPP_ */

#endif /* USE_FREETYPE */
