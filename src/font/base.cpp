/* 
    Title --- font/base.cpp

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


#ifndef _RPI_HW_FONT_BASE_CPP_
#define _RPI_HW_FONT_BASE_CPP_

#include <rpi-hw/font/base.hpp>
#include <rpi-hw/font/base-inl.hpp>

namespace rpihw { // Begin main namespace

namespace font { // Begin fonts namespace

base::base( const std::string &name, uint8_t height ) : m_name( name ), m_height( height ) {

}

base::~base() {

}

} // End of fonts namespace

} // End of main namespace

#endif
