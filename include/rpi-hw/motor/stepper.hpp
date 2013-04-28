/* 
    Title --- motor/stepper.hpp

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


#ifndef _RPI_HW_MOTOR_STEPPER_HPP_
#define _RPI_HW_MOTOR_STEPPER_HPP_

#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>
#include <rpi-hw/math.hpp>
#include <rpi-hw/time.hpp>

#include <rpi-hw/iface/base.hpp>
#include <rpi-hw/iface/output.hpp>

namespace rpihw { // Begin main namespace

/*!
	@namespace rpihw::motor
	@brief Namespace of the displays.
*/

namespace motor { // Begin motors namespace

//! Directions of the rotation.
enum Direction {

	DIRECTION_CW	=  1,	//!< Clockwise direction.
	DIRECTION_CCW	= -1	//!< Counterclockwise direction.
};

/*!
	@class stepper
	@brief Motor stepper controller.

	@example motor/28bjy48.cpp
*/
class stepper {

public:

	//@{
	//! Some moving sequences.
	static const uint8_t seq_2wire[4], seq_wave[4], seq_full[4], seq_half[8];
	//@}

	/*!
		@brief Constructor method.
		@param[in] steps The number of steps per revolution.
		@param[in] pin0 The GPIO pin connected to the data pin #0 of the stepper controller.
		@param[in] pin1 The GPIO pin connected to the data pin #1 of the stepper controller.
	*/
	stepper( size_t steps, uint8_t pin0, uint8_t pin1 );

	/*!
		@brief Constructor method.
		@param[in] steps The number of steps per revolution.
		@param[in] pin0 The GPIO pin connected to the data pin #0 of the stepper controller.
		@param[in] pin1 The GPIO pin connected to the data pin #1 of the stepper controller.
		@param[in] pin2 The GPIO pin connected to the data pin #2 of the stepper controller.
		@param[in] pin3 The GPIO pin connected to the data pin #3 of the stepper controller.
	*/
	stepper( size_t steps, uint8_t pin0, uint8_t pin1, uint8_t pin2, uint8_t pin3 );

	//! Destructor method.
	virtual ~stepper();

	/*!
		@brief Sets the number of steps per revolution.
		@param[in] steps The number of rotations per minute.
	*/
	void setSteps( size_t steps );

	/*!
		@brief Returns the number of steps per revolution.
		@return The current number of rotations per minute.
	*/
	size_t getSteps() const;

	/*!
		@brief Sets the moving sequence.
		@param[in] sequence The moving sequence.
		@param[in] len The length of the sequence.
	*/
	void setSequence( const uint8_t *sequence, uint8_t len = 0 );

	/*!
		@brief Sets the motor speed in rotations per minute (RPMs).
		@param[in] rpm The number of rotations per minute.
	*/
	void setSpeed( double rpm );

	/*!
		@brief Returns the motor speed in rotations per minute (RPMs).
		@return The currente number of rotations per minute.
	*/
	double getSpeed() const;

	/*!
		@brief Sets the motor direction.
		@param[in] direction The motor direction.
	*/
	void setDirection( Direction direction );

	/*!
		@brief Returns the current motor direction.
		@return The current motor direction.
	*/
	Direction getDirection() const;

	/*!
		@brief Moves the motor one or more steps.
		@param[in] number Number of steps.
	*/
	void step( size_t number = 1 );

	/*!
		@brief Rotates the motor.
		@param[in] angle The angle rotation (in degrees).
	*/
	void rotate( double angle );

protected:

	//! Output interface to the display.
	iface::output *m_motor;

	//! Moving sequence and its length.
	const uint8_t *m_sequence;

	//! Length of the moving sequence.
	uint8_t m_sequence_len;

	//! Motor direction.
	Direction m_direction;

	//! Motor speed in rotations per minute (RPMs).
	double m_rpm;

	//! Number of steps per revolution.
	size_t m_steps;

	//! Steps counter.
	size_t m_counter;
};

} // End of motors namespace

} // End of main namespace

#endif /* _RPI_HW_MOTOR_STEPPER_HPP_ */
