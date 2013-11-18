/* 
    Title --- sensor/hc-sr04.hpp

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


#ifndef _RPI_HW_SENSOR_HC_SR04_HPP_
#define _RPI_HW_SENSOR_HC_SR04_HPP_

#include <vector>
#include <chrono>

#include <sys/time.h>

#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>
#include <rpi-hw/math.hpp>
#include <rpi-hw/time.hpp>

#include <rpi-hw/iface/base.hpp>
#include <rpi-hw/iface/output.hpp>
#include <rpi-hw/iface/input.hpp>

// Use some external namespaces
using namespace std::chrono;

namespace rpihw { // Begin main namespace

/*!
	@namespace rpihw::sensor
	@brief Namespace of the sensors.
*/

namespace sensor { // Begin sensors namespace

/*!
	@class hcsr04
	@brief Ultrasonic distance sensor HC-SR04.

	@example sensor/hc-sr04.cpp
*/
class hcsr04 {

public:

	//! Used timer to measure the delay of pulse.
	using timer	= high_resolution_clock;

	/*!
		@brief Constructor method.
		@param[in] trigger The GPIO pin connected to the trigger.
		@param[in] echo The GPIO pin connected to the echo pin.
	*/
	hcsr04( uint8_t trigger, uint8_t echo );

	//! Destructor method.
	virtual ~hcsr04();

	/*!
		@brief Returns the elapsed time between sending and receiving back the pulse.
		@return The elapsed time in milliseconds.
	*/
	double timing();

	/*!
		@brief Returns the distance from the sensor to an object or surface.
		@return The distance in centimeters.
	*/
	double ranging();

protected:

	//! Output interface to the trigger.
	iface::output *m_trigger;

	//! Input interface connected to the echo pin.
	iface::input *m_echo;

	//! Time of last pulse sending.
	std::chrono::time_point< timer > m_last_sending;
};

} // End of sensors namespace

} // End of main namespace


// Include inline methods 
#include <rpi-hw/sensor/hc-sr04-inl.hpp>

#endif /* _RPI_HW_SENSOR_HC_SR04_HPP_ */
