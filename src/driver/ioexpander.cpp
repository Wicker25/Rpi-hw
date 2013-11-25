/* 
    Title --- driver/ioexpander.cpp

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


#ifndef _RPI_HW_DRIVER_IOEXPANDER_CPP_
#define _RPI_HW_DRIVER_IOEXPANDER_CPP_

#include <rpi-hw/driver/ioexpander.hpp>

namespace rpihw { // Begin main namespace

namespace driver { // Begin drivers namespace

void
ioexpander::setup( uint8_t pin, uint8_t mode, uint8_t pud_mode ) {

	throw exception( "(Fatal) `ioexpander::setup`: function is not implemented" );
}

void
ioexpander::write( uint8_t pin, bool value ) {

	throw exception( "(Fatal) `ioexpander::write`: function is not implemented" );
}

bool
ioexpander::read( uint8_t pin ) {

	throw exception( "(Fatal) `ioexpander::read`: function is not implemented" );
}

bool
ioexpander::checkEvent( uint8_t pin ) {

	throw exception( "(Fatal) `ioexpander::checkEvent`: function is not implemented" );
}

void
ioexpander::setRisingEvent( uint8_t pin, bool enabled ) {

	throw exception( "(Fatal) `ioexpander::setRisingEvent`: function is not implemented" );
}

void
ioexpander::setFallingEvent( uint8_t pin, bool enabled ) {

	throw exception( "(Fatal) `ioexpander::setFallingEvent`: function is not implemented" );
}

void
ioexpander::setHighEvent( uint8_t pin, bool enabled ) {

	throw exception( "(Fatal) `ioexpander::setHighEvent`: function is not implemented" );
}

void
ioexpander::setLowEvent( uint8_t pin, bool enabled ) {

	throw exception( "(Fatal) `ioexpander::setLowEvent`: function is not implemented" );
}

void
ioexpander::setPullUpDown( uint8_t pin, uint8_t mode ) {

	throw exception( "(Fatal) `ioexpander::setPullUpDown`: function is not implemented" );
}

} // End of drivers namespace

} // End of main namespace

#endif /* _RPI_HW_DRIVER_IOEXPANDER_CPP_ */
