/* 
    Title --- rpi-gpio.cpp [tools]

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


#include <iostream>
#include <cstdlib>
#include <cstring>

#include <rpi-hw.hpp>

#define RPI_GPIO_VERSION	"0.1"

static const char *usage =
"Usage: rpi-gpio <setup|edge|write|read> <gpio>\n\n"
"       rpi-gpio setup <gpio> <in|out|pulldown|pullup|pudoff>\n"
"       rpi-gpio write <gpio> <high|low>\n"
"       rpi-gpio edge  <gpio> <none|rising|falling|both>\n"
"       rpi-gpio read  <gpio>\n"
"       rpi-gpio -h\n"
"       rpi-gpio -v\n";


// Array con gli indici dei pin gpio
#if RPI_CPU_REVISION == 0002 || RPI_CPU_REVISION == 0003

//                       pin  =    0   1   2  3   4  5   6  7   8   9  10  11  12  13
static const int pin_gpio[27] = { -1, -1, -1, 0, -1, 1, -1, 4, 14, -1, 15, 17, 18, 21,
//								  14  15  16  17  18  19  20  21 22  23 24  25 26
								  -1, 22, 23, -1, 24, 10, -1, 9, 25, 11, 8, -1, 7 };

#else // if RPI_CPU_REVISION == 0002 || RPI_CPU_REVISION == 0004 || RPI_CPU_REVISION == 0006

//                       pin  =    0   1   2  3   4  5   6  7   8   9  10  11  12  13
static const int pin_gpio[27] = { -1, -1, -1, 2, -1, 3, -1, 4, 14, -1, 15, 17, 18, 27,
//								  14  15  16  17  18  19  20  21 22  23 24  25 26
								  -1, 22, 23, -1, 24, 10, -1, 9, 25, 11, 8, -1, 7 };
#endif


// Uso il namespace di Rpi-hw
using namespace rpihw;

int
main( int argc, char *args[] ) {

	// Flag di controllo
	bool success = false;

	// Controllo il numero minimo dei parametri
	if ( argc > 2 ) {

		// Gestore del controller gpio
		gpio io;

		// Ricavo il numero del pin scelto
	    char *garbage = NULL;
		uint8_t pin;

		// Copio il pin scelto oppure ricavo il pin della porta gpio
		if ( !strcasecmp( args[2], "pin" ) ) {

			pin = (int) strtol( ( args[2] + 3 ), &garbage, 0 );
			pin = ( *garbage == '\0' && pin >= 0 && pin < 27 ) ? (uint8_t) pin_gpio[pin] : (uint8_t) -1;

		} else {

			pin = (int) strtol( args[2], &garbage, 0 );
			if ( *garbage != '\0' || pin < 0 || pin >= NUM_OF_PINS ) pin = (uint8_t) -1;
		}

		// Controllo che non ci siano errori nella scelta dei pin
		if ( pin != -1 ) {

			// Modalità di un pin
			if ( !strcasecmp( args[1], "setup" ) ) {

				// Controllo che sia stato passato il terzo paramentro
				if ( argc > 3 ) {

					// Imposto il gpio di ingresso
					if ( !strcasecmp( args[3], "in" ) || !strcasecmp( args[3], "input" ) ) {

						io.setup( pin, gpio::INPUT );
						success = true;

					// Imposto il gpio di uscita
					} else if ( !strcasecmp( args[3], "out" ) || !strcasecmp( args[3], "output" ) ) {

						io.setup( pin, gpio::OUTPUT );
						success = true;

					// Imposto la modalità pull-down
					} else if ( !strcasecmp( args[4], "pulldown" ) ) {

						io.setPullUpDown( pin, gpio::PULL_DOWN );
						success = true;

					// Imposto la modalità pull-up
					} else if ( !strcasecmp( args[4], "pullup" ) ) {

						io.setPullUpDown( pin, gpio::PULL_UP );
						success = true;

					// Disabilito la modalità pull-up/down
					} else if ( !strcasecmp( args[4], "pudoff" ) ) {

						io.setPullUpDown( pin, gpio::PUD_OFF );
						success = true;
					}
				}

			// Lettura da un pin di ingresso
			} else if ( !strcasecmp( args[1], "edge" ) ) {

				// Estraggo gli eventi del pin
				int mode = -1;

				// Controllo che sia stato passato il terzo paramentro
				if ( argc > 3 ) {

					if ( !strcasecmp( args[3], "none" ) )
						mode = 0;
					else if ( !strcasecmp( args[3], "rising" ) )
						mode = 1;
					else if ( !strcasecmp( args[3], "falling" ) )
						mode = 2;
					else if ( !strcasecmp( args[3], "both" ) )
						mode = 3;
				}

				// Controllo che non ci siano errori nei parametri
				if ( mode != -1 ) {

					// Imposto gli eventi del pin
					io.setRisingEvent( pin, mode == 1 || mode == 3 );
					io.setFallingEvent( pin, mode == 2 || mode == 3 );

					// Imposto il flag di controllo
					success = true;
				}

			// Scrittura su un pin di uscita
			} else if ( !strcasecmp( args[1], "write" ) ) {

				// Estraggo il valore di uscita del pin
				int value = -1;

				// Controllo che sia stato passato il terzo paramentro
				if ( argc > 3 ) {

					if ( *args[3] == '0' || !strcasecmp( args[3], "low" ) )
						value = gpio::LOW;
					else if ( *args[3] == '1' || !strcasecmp( args[3], "high" ) )
						value = gpio::HIGH;
				}

				// Controllo che non ci siano errori nei parametri
				if ( value != -1 ) {

					// Scrivo il valore di uscita del pin
					io.write( pin, value );
					success = true;
				}

			// Lettura da un pin di ingresso
			} else if ( !strcasecmp( args[1], "read" ) ) {

				// Scrivo a schermo il valore di ingresso del pin
				std::cout << io.read( pin ) << std::endl;
				success = true;
			}
		}
	}

	if ( argc > 1 ) {

		// Stampo la versione dell'utility
		if ( !strcasecmp( args[1], "-v" ) ) {

			std::cout << "rpi-gpio v" << RPI_GPIO_VERSION << " by Giacomo Trudu aka `Wicker25`" << std::endl;
			success = true;

		// Stampo il manuale d'utilizzo
		} else if ( !strcasecmp( args[1], "-h" ) ) {

			std::cout << usage << std::endl;
			success = true;
		}
	}

	// Processo eventuali errori
	if ( !success ) {

		std::cout << usage << std::endl;
	}

	return 0;
}
