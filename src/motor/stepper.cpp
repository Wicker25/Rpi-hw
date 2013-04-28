/* 
    Title --- motor/stepper.cpp

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


#ifndef _RPI_HW_MOTOR_STEPPER_CPP_
#define _RPI_HW_MOTOR_STEPPER_CPP_

#include <rpi-hw/motor/stepper.hpp>

#include <rpi-hw/time.hpp>
#include <rpi-hw/time-inl.hpp>

#include <rpi-hw/gpio.hpp>
#include <rpi-hw/gpio-inl.hpp>

#include <rpi-hw/iface/base.hpp>
#include <rpi-hw/iface/base-inl.hpp>

#include <rpi-hw/iface/output.hpp>
#include <rpi-hw/iface/output-inl.hpp>

#include <rpi-hw/motor/stepper-inl.hpp>

namespace rpihw { // Begin main namespace

namespace motor { // Begin motors namespace

// Two wire sequence
const uint8_t stepper::seq_2wire[4] = {

	0x01,	// 0001
	0x03,	// 0011
	0x02,	// 0010
	0x00	// 0000
};

// Wave drive sequence
const uint8_t stepper::seq_wave[4] = {

	0x01,	// 0001
	0x02,	// 0010
	0x04,	// 0100
	0x08	// 1000
};

// Full step sequence
const uint8_t stepper::seq_full[4] = {

	0x03,	// 0011
	0x06,	// 0110
	0x0c,	// 1100
	0x09	// 1001
};

// Half step sequence
const uint8_t stepper::seq_half[8] = {

	0x01,	// 0001
	0x03,	// 0011
	0x02,	// 0010
	0x06,	// 0110
	0x04,	// 0100
	0x0c,	// 1100
	0x08,	// 1000
	0x09	// 1001
};


stepper::stepper( size_t steps, uint8_t pin0, uint8_t pin1 ) : m_direction( DIRECTION_CW ), m_rpm(1.0), m_steps( steps ) {

	// Create the output interface to the motor
	m_motor = new iface::output( 2, pin0, pin1 );

	// Set the moving sequence
	setSequence( stepper::seq_2wire, 4 );
}

stepper::stepper( size_t steps, uint8_t pin0, uint8_t pin1, uint8_t pin2, uint8_t pin3 ) : m_direction( DIRECTION_CW ), m_rpm(1.0), m_steps( steps ) {

	// Create the output interface to the motor
	m_motor = new iface::output( 4, pin0, pin1, pin2, pin3 );

	// Set the moving sequence
	setSequence( stepper::seq_half, 8 );
}

stepper::~stepper() {

	// Destroy the output interface
	delete m_motor;
}

void
stepper::setSequence( const uint8_t *sequence, uint8_t len ) {

	// Set the moving sequence and its length
	m_sequence		= sequence;
	m_sequence_len	= len;

	// Use the length of the default sequences
	if ( !len ) {

		if ( m_sequence == stepper::seq_2wire ||
			 m_sequence == stepper::seq_wave  ||
			 m_sequence == stepper::seq_full )

			m_sequence_len = 4;

		else if ( m_sequence == stepper::seq_half )
			m_sequence_len = 8;
	}
}

void
stepper::step( size_t number ) {

	// Calculate the delay time between signals (in microseconds)
	size_t delay = math::floor( ( 60000000.0 / m_rpm ) / (double) m_steps );

	// Move the motor
	size_t i = 0;

	for ( ; i < number; ++i ) {

		// Update the outputs to the motor 
		m_counter += (size_t) m_direction;
		m_motor->write( m_sequence[ m_counter % m_sequence_len ] );

		// Wait some time and increment the step counter
		time::usleep( delay );
	}
}

} // End of motors namespace

} // End of main namespace

#endif /* _RPI_HW_MOTOR_STEPPER_CPP_ */
