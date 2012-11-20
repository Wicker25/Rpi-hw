/* 
    Title --- display/m7seg.hpp

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


#ifndef _RPI_HW_DISPLAY_M7SEG_HPP_
#define _RPI_HW_DISPLAY_M7SEG_HPP_

#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>
#include <rpi-hw/math.hpp>

#include <rpi-hw/mutex.hpp>
#include <rpi-hw/thread.hpp>

#include <rpi-hw/iface/base.hpp>
#include <rpi-hw/iface/output.hpp>

#include <rpi-hw/display/s7seg.hpp>

namespace rpihw { // Begin main namespace

namespace display { // Begin displays namespace

// Display segments
/*
         a
       #####
    f #     # b
      #  g  #
       #####
    e #     # c
      #     #
       #####  # dp
         d
*/

/* MULTIPLE SEVEN-SEGMENT DISPLAY CONTROLLER */
class m7seg : public s7seg {

public:

	// Constructor and destructor methods
	m7seg( uint8_t a, uint8_t b, uint8_t c, uint8_t d,
		   uint8_t e, uint8_t f, uint8_t g, uint8_t dp = iface::DISABLED_PIN );
	virtual ~m7seg();

	// Sets the number of displays and the enabler interface
	virtual void setDisplays( size_t total, iface::output &enabler );

	// Sets the updating frequency (Hz)
	virtual void setFreq( float frequency );
	// Returns the updating frequency (Hz)
	virtual float getFreq() const;

	// Sets the value of the display
	virtual void set( float value );

	// Sets the format of the display
	virtual void format( uint8_t decimals, bool zeropad );

	// Rendering function
	virtual void render();

protected:

	// Enabler interface
	iface::output *m_enabler;

	// Rendering thread and mutex
	thread< m7seg > *m_thread;
	mutex *m_mutex;

	// Number of displays
	size_t m_ndisplay;

	// Updating frequency (Hz)
	float m_frequency;

	// Number of decimals
	uint8_t m_decimals;

	// Zeropad flag
	bool m_zeropad;
};

} // End of displays namespace

} // End of main namespace

#endif
