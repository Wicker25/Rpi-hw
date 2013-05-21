/* 
    Title --- time.cpp

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


#ifndef _RPI_HW_TIME_CPP_
#define _RPI_HW_TIME_CPP_

#include <rpi-hw/time.hpp>

namespace rpihw { // Begin main namespace

namespace time { // Begin time namespace

void
nsleep( size_t nseconds ) {

	// Use a high-resolution timer to wait some nanoseconds
	using timer	= high_resolution_clock;

	size_t elapsed;
	time_point< timer > start = timer::now();

	do {

		elapsed = duration_cast< nanoseconds >( timer::now() - start ).count();

	} while ( elapsed < nseconds );
}

} // End of times namespace

} // End of main namespace

#endif /* _RPI_HW_TIME_CPP_ */
