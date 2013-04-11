/* 
    Title --- bitmap.cpp

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


#ifndef _RPI_HW_BITMAP_CPP_
#define _RPI_HW_BITMAP_CPP_

#include <rpi-hw/bitmap.hpp>

#include <rpi-hw/utils.hpp>
#include <rpi-hw/utils-inl.hpp>

#include <rpi-hw/bitmap-inl.hpp>

namespace rpihw { // Begin main namespace

bitmap::bitmap( size_t width, size_t height, uint8_t *data ) : m_width( width ), m_height( height ), m_data( data ) {

}

bitmap::~bitmap() {

}

} // End of main namespace

#endif
