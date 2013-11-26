/* 
    Title --- consts.hpp [main]

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


#ifndef _RPI_HW_CONSTS_HPP_
#define _RPI_HW_CONSTS_HPP_

namespace rpihw { // Begin main namespace

//! Logic level.
enum Level {

	LOW		= 0,
	HIGH	= 1
};

//! Pin mode.
enum PinMode {

	INPUT		= 0,
	OUTPUT		= 1,
	PWM_OUTPUT	= 2
};

//! Pull control mode.
enum PullMode {

	PULL_OFF	= 0,
	PULL_DOWN	= 1,
	PULL_UP		= 2
};

} // End of main namespace

#endif /* _RPI_HW_CONSTS_HPP_ */
