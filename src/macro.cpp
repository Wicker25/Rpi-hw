/* 
    Title --- macro.cpp

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


#ifndef _RPI_HW_MACRO_CPP_
#define _RPI_HW_MACRO_CPP_

#include <rpi-hw/macro.hpp>

namespace rpihw { // Namespace di Rpi-hw

namespace macro { // Namespace delle funzioni macro

std::string format( const char *format, ... ) {

	// Buffer della stringa
	char buffer[256];

	// Leggo la lista degli argomenti
	va_list args;
	va_start( args, format );

	// Comunico il messaggio all'utente
	std::vsnprintf( buffer, 256, format, args );

	// Pulisco la lista degli argomenti
	va_end( args );

	// Ritorno l'oggetto stringa
	return std::string( buffer );
}

} // Chiudo il namespace delle funzioni macro

} // Chiudo il namespace di Rpi-hw

#endif
