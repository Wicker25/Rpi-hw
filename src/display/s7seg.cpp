/* 
    Title --- display/s7seg.cpp

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


#ifndef _RPI_HW_DISPLAY_S7SEG_CPP_
#define _RPI_HW_DISPLAY_S7SEG_CPP_

#include <rpi-hw/display/s7seg.hpp>

#include <rpi-hw/gpio.hpp>
#include <rpi-hw/gpio-inl.hpp>

#include <rpi-hw/iface/base.hpp>
#include <rpi-hw/iface/base-inl.hpp>

#include <rpi-hw/iface/output.hpp>
#include <rpi-hw/iface/output-inl.hpp>

#include <rpi-hw/display/s7seg-inl.hpp>

namespace rpihw { // Begin main namespace

namespace display { // Begin displays namespace

// Outputs of digits
const uint8_t s7seg::output[12] = {

	//				dp g f e d c b a
	0x3f,	// 0	 0 0 1 1 1 1 1 1
	0x06,	// 1	 0 0 0 0 0 1 1 0
	0x5b,	// 2	 0 1 0 1 1 0 1 1
	0x4f,	// 3	 0 1 0 0 1 1 1 1
	0x66,	// 4	 0 1 1 0 0 1 1 0
	0x6d,	// 5	 0 1 1 0 1 1 0 1
	0x7d,	// 6	 0 1 1 1 1 1 0 1
	0x07,	// 7	 0 0 0 0 0 1 1 1
	0x7f,	// 8	 0 1 1 1 1 1 1 1
	0x6f,	// 9	 0 1 1 0 1 1 1 1
	0x80,	// .	 1 0 0 0 0 0 0 0
	0x40,	// -	 0 1 0 0 0 0 0 0
};


s7seg::s7seg( uint8_t a, uint8_t b, uint8_t c,
			  uint8_t d, uint8_t e, uint8_t f, uint8_t g ) {

	// Create the output interface to the display
	m_display = new iface::output( 7, a, b, c, d, e, f, g );
}

s7seg::s7seg( uint8_t a, uint8_t b, uint8_t c, uint8_t d,
			  uint8_t e, uint8_t f, uint8_t g, uint8_t dp ) {

	// Create the output interface to the display
	m_display = new iface::output( 8, a, b, c, d, e, f, g, dp );
}

s7seg::~s7seg() {

	// Destroy the output interface
	delete m_display;
}

void
s7seg::set( float value ) {

	// Store the value of the display
	m_value = value;

	// Set the outputs corresponding to the value
	m_display->write( s7seg::output[ (uint8_t) math::floor( value ) % 10 ] );
}

} // End of displays namespace

} // End of main namespace

#endif
