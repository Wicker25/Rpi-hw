/* 
    Title --- iface/encoder-out.cpp

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


#ifndef _RPI_HW_IFACE_ENCODER_OUT_CPP_
#define _RPI_HW_IFACE_ENCODER_OUT_CPP_

#include <rpi-hw/iface/encoder-out.hpp>

namespace rpihw { // Begin main namespace

namespace iface { // Begin interfaces namespace

encoderOut::encoderOut( std::initializer_list< uint8_t > pins ) : iface::output( pins ) {

}

encoderOut::encoderOut( const std::vector< uint8_t > &pins ) : iface::output( pins ) {

}

encoderOut::~encoderOut() {

}

} // End of interfaces namespace

} // End of main namespace

#endif /* _RPI_HW_IFACE_ENCODER_OUT_CPP_ */
