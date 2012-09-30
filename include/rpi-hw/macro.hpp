/* 
    Title --- macro.hpp

    Copyright (C) 2010 Giacomo Trudu - wicker25[at]gmail[dot]com

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


#ifndef _RPI_HW_MACRO_HPP_
#define _RPI_HW_MACRO_HPP_

#include <cstdio>
#include <cstdarg>
#include <string>

namespace rpihw { // Namespace di Rpi-hw

namespace macro { // Namespace delle funzioni macro

// Ritorna un oggetto stringa formattato come in `printf`
std::string format( const char *format, ... );

} // Chiudo il namespace delle funzioni macro

} // Chiudo il namespace di Rpi-hw

#endif
