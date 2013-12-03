/* 
    Title --- motor/hcsr04.cpp

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


#ifndef _RPI_HW_SENSOR_HCSR04_CPP_
#define _RPI_HW_SENSOR_HCSR04_CPP_

#include <rpi-hw/sensor/hcsr04.hpp>

namespace rpihw { // Begin main namespace

namespace sensor { // Begin sensors namespace

hcsr04::hcsr04( uint8_t trigger, uint8_t echo )

	: m_trigger			( new iface::output( { trigger } ) )
	, m_echo			( new iface::input( { echo } ) )
	, m_last_sending	( timer::now() ) {

}

hcsr04::~hcsr04() {

	// Destroy the interfaces
	delete m_trigger;
	delete m_echo;
}

double
hcsr04::timing() {

	time_point< timer > start, end;

	// Make sure that enough time has passed since last pulse
	size_t elapsed = duration_cast< milliseconds >( timer::now() - m_last_sending ).count();

	if ( elapsed < 250 )
		time::msleep( 250 - elapsed );

	// Send 10us pulse to the trigger
	m_trigger->write( 0, 1 );
	time::nsleep( 10000 );
	m_trigger->write( 0, 0 );

	// Calculate the time elapsed from the pulse sending
	start = timer::now();

	while ( !m_echo->read(0) )
		start = timer::now();

	while ( m_echo->read(0) )
		end = timer::now();

	// Store the sending time
	m_last_sending = timer::now();

	// Return the elapsed time between sending and receiving back the pulse
	return (double) duration_cast< nanoseconds >( end - start ).count() / 1000000;
}

} // End of sensors namespace

} // End of main namespace

#endif /* _RPI_HW_SENSOR_HCSR04_CPP_ */
