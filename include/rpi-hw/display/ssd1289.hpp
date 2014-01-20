/* 
    Title --- display/ssd1289.hpp

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


#ifndef _RPI_HW_DISPLAY_SSD1289_HPP_
#define _RPI_HW_DISPLAY_SSD1289_HPP_

#include <rpi-hw/preprocessor/enumerate.hpp>

#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>
#include <rpi-hw/math.hpp>
#include <rpi-hw/utils.hpp>

#include <rpi-hw/designer.hpp>

#include <rpi-hw/iface/output.hpp>

namespace rpihw { // Begin main namespace

namespace display { // Begin displays namespace

/*!
	@class ssd1289
	@brief SSD1289 LCD controller.

	@example display/ssd1289.cpp
*/
class ssd1289 : public designer< int16_t, uint16_t, 3 > {

public:

	//! The size of the display.
	enum DisplaySize {

		LCD_WIDTH	= 240,
		LCD_HEIGHT	= 320
	};

	//! The orientation of the display.
	enum DisplayOrientation {

		PORTRAIT	= 0,
		LANDSCAPE	= 1
	};

	/*!
		@brief Constructor method (4-bit mode).
		@param[in] rs .
		@param[in] wr .
		@param[in] rd .
		@param[in] cs .
		@param[in] rst .
		@param[in] d0...d15 The GPIO pin connected to the data pins.
	*/
	ssd1289( uint8_t rs, uint8_t wr, uint8_t rd, uint8_t cs, uint8_t rst, __ENUM_PARAMS( uint8_t, db, 0, 15 ) );

	//! Destructor method.
	virtual ~ssd1289();

	/*!
		@brief Initializes the display.
		@param[in] orientation The display aspect (portrait or landscape).
	*/
	void init( bool orientation = PORTRAIT );

protected:

	//! Output interface to the control pins.
	iface::output *m_control;

	//! Output interface to the data pins.
	iface::output *m_data;
};

} // End of displays namespace

} // End of main namespace


// Include inline methods 
#include <rpi-hw/display/ssd1289-inl.hpp>

#endif /* _RPI_HW_DISPLAY_SSD1289_HPP_ */
