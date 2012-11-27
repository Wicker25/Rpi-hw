/* 
    Title --- display/s7seg.hpp

    Copyright (C) 2012 Giacomo Trudu - wicker25[at]gmail[dot]com

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


#ifndef _RPI_HW_DISPLAY_S7SEG_HPP_
#define _RPI_HW_DISPLAY_S7SEG_HPP_

#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>
#include <rpi-hw/math.hpp>

#include <rpi-hw/iface/base.hpp>
#include <rpi-hw/iface/output.hpp>

namespace rpihw { // Begin main namespace

/*!
	@namespace rpihw::display
	@brief Namespace of the displays.
*/

namespace display { // Begin displays namespace

/* SEVEN-SEGMENT DISPLAY CONTROLLER */
/*!
	@class s7seg
	@brief Seven-segment display controller.

	@example s7seg.cpp
*/
class s7seg {

public:

	//! Display segments
	enum Segments {

		SEGMENT_A	= 0,
		SEGMENT_B	= 1,
		SEGMENT_C	= 2,
		SEGMENT_D	= 3,
		SEGMENT_E	= 4,
		SEGMENT_F	= 5,
		SEGMENT_G	= 6,
		SEGMENT_DP	= 7
	};

	//! Outputs of digits
	static const uint8_t output[12];

	/*!
		@brief Constructor method.
		@param[in] a The GPIO pin connected to the segment a.
		@param[in] b The GPIO pin connected to the segment b.
		@param[in] c The GPIO pin connected to the segment c.
		@param[in] d The GPIO pin connected to the segment d.
		@param[in] e The GPIO pin connected to the segment e.
		@param[in] f The GPIO pin connected to the segment f.
		@param[in] g The GPIO pin connected to the segment g.
		@param[in] dp The GPIO pin connected to the segment dp (decimal point).
	*/
	s7seg( uint8_t a, uint8_t b, uint8_t c, uint8_t d,
		   uint8_t e, uint8_t f, uint8_t g, uint8_t dp = iface::DISABLED_PIN );

	//! Destructor method.
	virtual ~s7seg();

	/*!
		@brief Sets the value of the display.
		@param[in] value The new value of the display.
	*/
	virtual void set( float value );

	/*!
		@brief Returns the value of the display.
		@return The current value of the display.
	*/
	virtual float get() const;

protected:

	//! Output interface to the display.
	iface::output *m_display;

	//! Value of the display.
	float m_value;
};

} // End of displays namespace

} // End of main namespace

#endif
