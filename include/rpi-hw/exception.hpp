/* 
    Title --- exception.hpp

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


#ifndef _RPI_HW_EXCEPTION_HPP_
#define _RPI_HW_EXCEPTION_HPP_

#include <rpi-hw/macro.hpp>

#include <stdexcept>

#define exception( x ) exception_class( __FILE__, __LINE__, x )

namespace rpihw { // Namespace di Rpi-hw

/* ECCEZIONE */

class exception_class : public std::runtime_error {

public:

	// Metodo costruttore
	exception_class( const char *file, size_t line, const std::string &message ) :
		std::runtime_error( macro::format( "%s:%lu: \n\t\t", file, line ) + message ) { }
};

} // Chiudo il namespace di Rpi-hw

#endif
