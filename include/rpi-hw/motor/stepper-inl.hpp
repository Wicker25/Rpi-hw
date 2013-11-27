/* 
    Title --- motor/stepper-inl.hpp

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


#ifndef _RPI_HW_MOTOR_STEPPER_INL_HPP_
#define _RPI_HW_MOTOR_STEPPER_INL_HPP_

namespace rpihw { // Begin main namespace

namespace motor { // Begin motors namespace

inline void
stepper::setSteps( size_t steps ) {

	// Set the number of steps per revolution
	m_steps = steps;
}

inline size_t
stepper::getSteps() const {

	// Return the number of steps per revolution
	return m_steps;
}

inline void
stepper::setSpeed( double rpm ) {

	// Set the motor speed in rotations per minute
	m_rpm = math::abs( rpm );
}

inline double
stepper::getSpeed() const {

	// Return the motor speed in rotations per minute
	return m_rpm;
}

inline void
stepper::setDirection( Direction direction ) {

	// Set the motor direction
	m_direction = direction;
}

inline Direction
stepper::getDirection() const {

	// Return the current motor direction
	return m_direction;
}

} // End of motors namespace

} // End of main namespace

#endif /* _RPI_HW_MOTOR_STEPPER_INL_HPP_ */
