/* 
	Title --- display/itdb02.cpp

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


#ifndef _RPI_HW_DISPLAY_ITDB02_CPP_
#define _RPI_HW_DISPLAY_ITDB02_CPP_

#include <rpi-hw/display/itdb02.hpp>

namespace rpihw { // Begin main namespace

namespace display { // Begin displays namespace

itdb02::itdb02( uint8_t rs, uint8_t wr, uint8_t rd, uint8_t cs, uint8_t rst, __ENUM_PARAMS( uint8_t, db, 0, 15 ) )

	: designer< int16_t, uint16_t, 3 >	( LCD_WIDTH, LCD_HEIGHT )
	, m_control							( new iface::output( { rs, wr, rd, cs, rst } ) )
	, m_data							( new iface::output( { __ENUM_FROM_TO( db, 0, 15 ) } ) ) {

}

itdb02::~itdb02() {

	// Destroy the interfaces
	delete m_control;
	delete m_data;
}

} // End of displays namespace

} // End of main namespace

#endif /* _RPI_HW_DISPLAY_ITDB02_CPP_ */
