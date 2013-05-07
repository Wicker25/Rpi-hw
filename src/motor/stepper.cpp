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

namespace rpihw { // Begin main namespace

namespace motor { // Begin motors namespace

// Two wire sequence
const std::vector< uint8_t > stepper::seq_2wire = {

	0x01,	// 0001
	0x03,	// 0011
	0x02,	// 0010
	0x00	// 0000
};

// Wave drive sequence
const std::vector< uint8_t > stepper::seq_wave = {

	0x01,	// 0001
	0x02,	// 0010
	0x04,	// 0100
	0x08	// 1000
};

// Full step sequence
const std::vector< uint8_t > stepper::seq_full = {

	0x03,	// 0011
	0x06,	// 0110
	0x0c,	// 1100
	0x09	// 1001
};

// Half step sequence
const std::vector< uint8_t > stepper::seq_half = {

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
	m_motor = new iface::output( { pin0, pin1 } );

	// Set the moving sequence
	setSequence( stepper::seq_2wire );
}

stepper::stepper( size_t steps, uint8_t pin0, uint8_t pin1, uint8_t pin2, uint8_t pin3 ) : m_direction( DIRECTION_CW ), m_rpm(1.0), m_steps( steps ) {

	// Create the output interface to the motor
	m_motor = new iface::output( { pin0, pin1, pin2, pin3 } );

	// Set the moving sequence
	setSequence( stepper::seq_half );
}

stepper::~stepper() {

	// Destroy the output interface
	delete m_motor;
}

void
stepper::setSequence( const std::vector< uint8_t > &sequence ) {

	// Set the moving sequence and its length
	m_sequence = sequence;
}

void
stepper::step( size_t number ) {

	// Calculate the delay time between signals (in microseconds)
	size_t delay = math::floor( ( 60000000.0 / m_rpm ) / (double) m_steps );

	// Get the sequence length;
	uint8_t sequence_len = (uint8_t) m_sequence.size();

	// Move the motor
	size_t i = 0;

	for ( ; i < number; ++i ) {

		// Update the outputs to the motor 
		m_counter += (size_t) m_direction;
		m_motor->write( m_sequence[ m_counter % sequence_len ] );

		// Wait some time and increment the step counter
		time::usleep( delay );
	}
}

} // End of motors namespace

} // End of main namespace

#endif /* _RPI_HW_MOTOR_STEPPER_CPP_ */
