/* 
    Title --- font/freetype.cpp

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


#ifndef _RPI_HW_FONT_FREETYPE_CPP_
#define _RPI_HW_FONT_FREETYPE_CPP_

#include <rpi-hw/font/freetype.hpp>

#include <rpi-hw/font/base.hpp>
#include <rpi-hw/font/base-inl.hpp>

#include <rpi-hw/font/freetype-inl.hpp>

namespace rpihw { // Begin main namespace

namespace font { // Begin fonts namespace

FT_Error
faceRequester( FTC_FaceID face_id, FT_Library library, FT_Pointer obj, FT_Face *face ) {

	// Call the method of the object
	((freetype *) obj)->buildFace( face_id, face );

	return 0;
}

freetype::freetype( const std::string &name, uint8_t height, RenderMode mode ) : font::base( name, height ) {

	// Initialize the FreeType Font Library
	if ( FT_Init_FreeType( &m_library ) )
		throw exception( "(Error) FT_Init_FreeType: failed\n" );

	// Create the cache manager and some other instances
	if ( FTC_Manager_New( m_library, 0, 0, 0, (FTC_Face_Requester) &faceRequester, (FT_Pointer *) this, &m_manager ) )
		throw exception( "(Error) FTC_Manager_New: failed\n" );

	if ( FTC_CMapCache_New( m_manager, &m_cmap_cache ) )
		throw exception( "(Error) FTC_CMapCache_New: failed\n" );

	if ( FTC_SBitCache_New( m_manager, &m_sbit_cache ) )
		throw exception( "(Error) FTC_SBitCache_New: failed\n" );


	// Set the parameters of the font
	m_image_type = new FTC_ImageTypeRec;

	m_image_type->face_id	= 0;
	m_image_type->width		= height;
	m_image_type->height	= height;
	m_image_type->flags		= FT_LOAD_DEFAULT;

	// Set the font rendering mode
	if ( mode == RENDER_MONOCHROME )
		m_image_type->flags |= FT_LOAD_RENDER | FT_LOAD_MONOCHROME | FT_LOAD_TARGET_MONO;
}

freetype::~freetype() {

	// Free the memory
	FT_Done_FreeType( m_library );
}

void
freetype::buildFace( FTC_FaceID face_id, FT_Face *face ) {

	// Build the fresh new font object
	if ( FT_New_Face( m_library, (const char *) m_name.c_str(), 0, face ) )
		throw exception( "(Error) FT_New_Face: unknow file format\n" );
}

void
freetype::getSBitChar( uint32_t charcode, FTC_SBit &sbit ) const {

	// Translate the character code into a glyph index
	FT_UInt glyph_index = FTC_CMapCache_Lookup( m_cmap_cache, m_image_type->face_id, 0, charcode );

	if ( !glyph_index )
		throw exception( "(Error) FTC_CMapCache_Lookup: failed\n" );

	if ( FTC_SBitCache_Lookup( m_sbit_cache, m_image_type, glyph_index, &sbit, NULL ) )
		throw exception( "(Error) FTC_SBitCache_Lookup: failed\n" );
}

uint8_t
freetype::getWidth( uint32_t charcode ) const {

	// Get the bitmap of the character
	FTC_SBit sbit;

	getSBitChar( charcode, sbit );

	// Return the width of the character
	return sbit->width;
}

void
freetype::data( uint32_t charcode, glyph &glyph ) const {

	// Get the bitmap of the character
	FTC_SBit sbit;

	getSBitChar( charcode, sbit );

	// Copy the bitmap informations to the glyph object
	glyph.width		= (uint8_t) sbit->width;
	glyph.height	= (uint8_t) sbit->height;

	glyph.left		= (int8_t) sbit->left;
	glyph.top		= (int8_t) sbit->top;

	glyph.format	= (uint8_t)	sbit->format;
	glyph.grays		= (uint8_t)	sbit->max_grays;
	glyph.pitch		= (int8_t)	sbit->pitch;

	glyph.xadvance	= (int8_t) sbit->xadvance;
	glyph.yadvance	= (int8_t) sbit->yadvance;

	glyph.buffer	= (const uint8_t *) sbit->buffer;
}

} // End of fonts namespace

} // End of main namespace

#endif
