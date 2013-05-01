/* 
    Title --- display/m7seg.cpp

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


#ifndef _RPI_HW_DISPLAY_M7SEG_CPP_
#define _RPI_HW_DISPLAY_M7SEG_CPP_

#include <rpi-hw/display/m7seg.hpp>

namespace rpihw { // Begin main namespace

namespace display { // Begin displays namespace

m7seg::m7seg( uint8_t a, uint8_t b, uint8_t c,
			  uint8_t d, uint8_t e, uint8_t f, uint8_t g ) : s7seg( a, b, c, d, e, f, g ) {

	// Initialize the instance
	init();
}

m7seg::m7seg( uint8_t a, uint8_t b, uint8_t c, uint8_t d,
			  uint8_t e, uint8_t f, uint8_t g, uint8_t dp ) : s7seg( a, b, c, d, e, f, g, dp ) {

	// Initialize the instance
	init();
}

m7seg::~m7seg() {

	// Destroy the rendering thread and mutex
	delete m_thread;
	delete m_mutex;
}

void
m7seg::init() {

	// Initialize some structures
	m_enabler	= NULL;
	m_ndisplay	= 2;

	// Set the updating frequency (Hz)
	setFreq( 100.0 );

	// Set the format of the display
	format( 0, false );

	// Create the rendering thread and mutex
	m_thread	= new thread< m7seg >( *this, &m7seg::render );
	m_mutex		= new mutex;
}

void
m7seg::set( float value ) {

	// Store the value of the display
	m_mutex->lock();
	m_value = value;
	m_mutex->unlock();
}

void
m7seg::format( uint8_t decimals, bool zeropad ) {

	// Store the format of the display
	m_decimals = decimals;
	m_zeropad = zeropad;
}

void
m7seg::render() {

	// Value of the display
	size_t value;

	// Negative number flag
	bool negative;

	// Outputs to the display
	uint8_t out;

	// Iterator
	uint8_t i;

	// Rendering loop
	for ( ;; ) {

		// Check if the enabler interface has been set
		if ( m_enabler != NULL ) {

			// Acquire the mutex
			m_mutex->lock();

			// Calculate the value of the display
			negative = ( m_value < 0 );
			value = (size_t) math::floor( ( negative ? -m_value : m_value ) * math::pow( 10.0f, (float) m_decimals ) );

			// Initialize the outputs to the display
			out = 0xff;

			// Update all displays
			for ( i = 0; i < m_ndisplay && out; ++i ) {

				// Handle non-numeric symbols
				if ( !value && i > m_decimals ) {

					// Place the minus symbol
					if ( negative && !m_zeropad ) {

						out = m7seg::output[11];
						negative = false;

					} else if ( negative && m_zeropad && ( i == m_ndisplay - 1 ) )
						out = m7seg::output[11];

					// Zero pad
					else if ( m_zeropad )
						out = m7seg::output[0];

					// Otherwise, terminate loop 
					else out = 0;

				} else {

					// Set the outputs of the i-th digit
					out = m7seg::output[ value % 10 ];
					value /= 10;

					// Place the decimal point
					if ( m_decimals && i == m_decimals )
						out |= m7seg::output[10];
				}

				// Check if the outputs has been set
				if ( out ) {

					// Write the outputs to the i-th display
					m_display->write( out );

					// Enable the i-th display
					m_enabler->write( i );

					// Wait some time (corresponding to the rendering frequency)
					time::usleep( (size_t) ( 1000000.0 / getFreq() ) );
				}
			}

			// Release the mutex
			m_mutex->unlock();
		}
	}
}

} // End of displays namespace

} // End of main namespace

#endif /* _RPI_HW_DISPLAY_M7SEG_CPP_ */
