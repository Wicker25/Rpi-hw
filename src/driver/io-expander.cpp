/* 
    Title --- driver/io-expander.cpp

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


#ifndef _RPI_HW_DRIVER_IO_EXPANDER_CPP_
#define _RPI_HW_DRIVER_IO_EXPANDER_CPP_

#include <rpi-hw/driver/io-expander.hpp>

namespace rpihw { // Begin main namespace

namespace driver { // Begin drivers namespace

void
io_expander::setup( uint8_t pin, uint8_t mode, uint8_t pull_mode ) {

	throw exception( "(Fatal) `io_expander::setup`: function is not implemented" );
}

void
io_expander::write( uint8_t pin, bool value ) {

	throw exception( "(Fatal) `io_expander::write`: function is not implemented" );
}

bool
io_expander::read( uint8_t pin ) {

	throw exception( "(Fatal) `io_expander::read`: function is not implemented" );
}

bool
io_expander::checkEvent( uint8_t pin ) {

	throw exception( "(Fatal) `io_expander::checkEvent`: function is not implemented" );
}

void
io_expander::setRisingEvent( uint8_t pin, bool enabled ) {

	throw exception( "(Fatal) `io_expander::setRisingEvent`: function is not implemented" );
}

void
io_expander::setFallingEvent( uint8_t pin, bool enabled ) {

	throw exception( "(Fatal) `io_expander::setFallingEvent`: function is not implemented" );
}

void
io_expander::setHighEvent( uint8_t pin, bool enabled ) {

	throw exception( "(Fatal) `io_expander::setHighEvent`: function is not implemented" );
}

void
io_expander::setLowEvent( uint8_t pin, bool enabled ) {

	throw exception( "(Fatal) `io_expander::setLowEvent`: function is not implemented" );
}

void
io_expander::setPullUpDown( uint8_t pin, uint8_t mode ) {

	throw exception( "(Fatal) `io_expander::setPullUpDown`: function is not implemented" );
}

} // End of drivers namespace

} // End of main namespace

#endif /* _RPI_HW_DRIVER_IO_EXPANDER_CPP_ */
