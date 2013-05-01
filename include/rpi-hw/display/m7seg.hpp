/* 
    Title --- display/m7seg.hpp

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


#ifndef _RPI_HW_DISPLAY_M7SEG_HPP_
#define _RPI_HW_DISPLAY_M7SEG_HPP_

#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>
#include <rpi-hw/math.hpp>
#include <rpi-hw/time.hpp>

#include <rpi-hw/mutex.hpp>
#include <rpi-hw/thread.hpp>

#include <rpi-hw/iface/base.hpp>
#include <rpi-hw/iface/output.hpp>

#include <rpi-hw/display/s7seg.hpp>

namespace rpihw { // Begin main namespace

namespace display { // Begin displays namespace

/*!
	@class m7seg
	@brief Multiple seven-segment display controller.

	@example display/m7seg0.cpp
	@example display/m7seg1.cpp
*/
class m7seg : public s7seg {

public:

	/*!
		@brief Constructor method.
		@param[in] a The GPIO pin connected to the segment a.
		@param[in] b The GPIO pin connected to the segment b.
		@param[in] c The GPIO pin connected to the segment c.
		@param[in] d The GPIO pin connected to the segment d.
		@param[in] e The GPIO pin connected to the segment e.
		@param[in] f The GPIO pin connected to the segment f.
		@param[in] g The GPIO pin connected to the segment g.
	*/
	m7seg( uint8_t a, uint8_t b, uint8_t c, uint8_t d,
		   uint8_t e, uint8_t f, uint8_t g );

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
	m7seg( uint8_t a, uint8_t b, uint8_t c, uint8_t d,
		   uint8_t e, uint8_t f, uint8_t g, uint8_t dp );

	//! Destructor method.
	virtual ~m7seg();

	/*!
		@brief Sets the number of displays and the enabler interface.
		@param[in] total Number of the displays.
		@param[in] enabler Output interface used to enable the displays.
	*/
	void setDisplays( size_t total, iface::output &enabler );

	/*!
		@brief Sets the updating frequency.
		@param[in] frequency The updating frequency in Hz.
	*/
	void setFreq( float frequency );

	/*!
		@brief Returns the updating frequency.
		@return The updating frequency in Hz.
	*/
	float getFreq() const;

	/*!
		@brief Sets the value of the display.
		@param[in] value The new value of the display.
	*/
	void set( float value );

	/*!
		@brief Sets the format of the display.
		@param[in] decimals The number of decimals used to represent the value of the display.
		@param[in] zeropad If \c true, zero pad the value of the display.
	*/
	void format( uint8_t decimals, bool zeropad );

	//! Update the displays (threading function).
	void render();

protected:

	//! Enabler interface.
	iface::output *m_enabler;

	//! Rendering thread.
	thread< m7seg > *m_thread;

	//! Mutex of the rendering thread.
	mutex *m_mutex;

	//! Number of the displays.
	size_t m_ndisplay;

	//! Updating frequency (Hz).
	float m_frequency;

	//! Number of decimals.
	uint8_t m_decimals;

	//! Zeropad flag.
	bool m_zeropad;

	//! Initializes the instance.
	void init();
};

} // End of displays namespace

} // End of main namespace


// Include inline methods 
#include <rpi-hw/display/m7seg-inl.hpp>

#endif /* _RPI_HW_DISPLAY_M7SEG_HPP_ */
