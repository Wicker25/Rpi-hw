/* 
    Title --- display/pcd8544.hpp

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


#ifndef _RPI_HW_DISPLAY_PCD8544_HPP_
#define _RPI_HW_DISPLAY_PCD8544_HPP_

#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>
#include <rpi-hw/math.hpp>
#include <rpi-hw/utils.hpp>
#include <rpi-hw/time.hpp>

#include <rpi-hw/bitset.hpp>

#include <rpi-hw/designer.hpp>

#include <rpi-hw/iface/base.hpp>
#include <rpi-hw/iface/output.hpp>
#include <rpi-hw/iface/input.hpp>
#include <rpi-hw/iface/shiftout.hpp>

namespace rpihw { // Begin main namespace

namespace display { // Begin displays namespace

/*!
	@class pcd8544
	@brief Philips PCD8544 LCD controller.
*/
class pcd8544 : public designer< int8_t, bool > {

public:

	//! The controller command set.
	enum CommandSet {

		DISPLAY	= 0x08,		//!< Display control.
		FUNC	= 0x20,		//!< Function set.
		YADDR	= 0x40,		//!< Set Y address of RAM.
		XADDR	= 0x80,		//!< Set Y address of RAM.

		TEMP	= 0x04,		//!< Temperature control.
		BIAS	= 0x10,		//!< Bias system.
		VOP		= 0x80		//!< Set Vop.
	};

	//! The controller command set (bit flags).
	enum CommandArgs {

		DISPLAY_E	= 0x01,		//!< Sets display configuration.
		DISPLAY_D	= 0x04,		//!< Sets display configuration.

		FUNC_H		= 0x01,		//!< Extended instruction set.
		FUNC_V		= 0x02,		//!< Entry mode.
		FUNC_PD		= 0x04,		//!< Power down control.

		BIAS_BS0	= 0x01,		//!< Set bias system.
		BIAS_BS1	= 0x02,		//!< Set bias system.
		BIAS_BS2	= 0x04		//!< Set bias system.
	};

	//! The controller data pins.
	enum DataPin {

		DIN		= 0,	//!< Serial data input.
		SCLK	= 1,	//!< Input for the clock signal. 
		DC		= 0,	//!< Data/Command mode select.
		SCE		= 1,	//!< Chip Enable (CS/SS).
		RST		= 2		//!< External rst input.
	};

	//! The size of the display.
	enum DisplaySize {

		LCD_WIDTH	= 84,
		LCD_HEIGHT	= 48
	};

	//! The display colors.
	enum Color {

		COLOR_WHITE	= 0,
		COLOR_BLACK	= 1
	};

	/*!
		@brief Constructor method (4-bit mode).
		@param[in] sclk The GPIO pin connected to the sclk pin.
		@param[in] sdin The GPIO pin connected to the sda pin.
		@param[in] dc The GPIO pin connected to the dorc pin.
		@param[in] sce The GPIO pin connected to the cs pin.
		@param[in] rst The GPIO pin connected to the rst pin.
	*/
	pcd8544( uint8_t sclk, uint8_t sdin, uint8_t dc, uint8_t sce, uint8_t rst );

	//! Destructor method.
	virtual ~pcd8544();

	/*!
		@brief Initializes the display.
		@param[in] contrast The contrast of the display.
		@param[in] inverse Invert the colors of the display.
	*/
	void init( uint8_t contrast, bool inverse );

	/*!
		@brief Sends a command to the display.
		@param[in] data The command.
	*/
	void cmd( uint8_t data );

	/*!
		@brief Sends a data to the display.
		@param[in] data The 8-bit data to be sended.
	*/
	void sendData( uint8_t data );

	/*!
		@brief Sets the contrast of the display.
		@param[in] value The contrast of the display.
	*/
	void setContrast( uint8_t value );

	/*!
		@brief Sets the color of a pixel.
		@param[in] x The horizontal position of the pixel.
		@param[in] y The vertical position of the pixel.
		@param[in] color The new color of the pixel.
	*/
	virtual void setPixel( int8_t x, int8_t y, bool color );

	/*!
		@brief Sets the color of a pixel.
		@param[in] x The horizontal position of the pixel.
		@param[in] y The vertical position of the pixel.
		@return The current color of the pixel.
	*/
	virtual bool getPixel( int8_t x, int8_t y ) const;

	/*!
		@brief Redraws the display.
		@return The number of updated blocks.
	*/
	uint16_t redraw();

	//! Clears the display.
	void clear();

protected:

	//! Output interface to the control pins.
	iface::output *m_control;

	//! Shift-out interface to the data pins.
	iface::shiftOut *m_data;

	//! Data buffer.
	uint8_t *m_buffer;

	//! Buffer of updates.
	bitset *m_updates;

	/*!
		@brief Updates the bounding box.
		@param[in] left The left side of the bounding box.
		@param[in] top The top side of the bounding box.
		@param[in] right The right side of the bounding box.
		@param[in] bottom The bottom side of the bounding box.
	*/
	void updateBoundingBox( uint8_t left, uint8_t top, uint8_t right, uint8_t bottom );
};

} // End of displays namespace

} // End of main namespace

#endif
