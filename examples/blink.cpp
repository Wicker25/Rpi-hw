/* 
    Title --- blink.cpp [examples]

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


#include <rpi-hw.hpp>
#include <ctime>

using namespace rpihw;

int
main( int argc, char *args[] ) {

	// Gestore del controller gpio
	gpio io;

	// Imposto il gpio di uscita
	io.setup( 11, gpio::OUTPUT );

	// Alterno il segnale di uscita del gpio
	while ( 1 ) {

		io.write( 11, gpio::HIGH );
		usleep( 1000000 );
		io.write( 11, gpio::LOW );
		usleep( 1000000 );
	}

	return 0;
}

