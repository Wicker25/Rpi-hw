/* 
    Title --- sensor/hc-sr04-inl.hpp

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


#ifndef _RPI_HW_SENSOR_HC_SR04_INL_HPP_
#define _RPI_HW_SENSOR_HC_SR04_INL_HPP_

namespace rpihw { // Begin main namespace

namespace sensor { // Begin sensors namespace

inline double
hcsr04::ranging() {

	// Return the distance from the sensor to an object or surface
	return timing() * 17;
}

} // End of sensors namespace

} // End of main namespace

#endif /* _RPI_HW_SENSOR_HC_SR04_INL_HPP_ */
