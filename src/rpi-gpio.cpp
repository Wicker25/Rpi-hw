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

using namespace rpihw;

// Array con gli indici dei pin gpio
#if RPI_CPU_REVISION == 0002 || RPI_CPU_REVISION == 0003

//                       pin  =    0   1   2  3   4  5   6  7   8   9  10  11  12  13  14  15  16  17  18  19  20  21 22  23 24  25 26
static const int pin_gpio[27] = { -1, -1, -1, 0, -1, 1, -1, 4, 14, -1, 15, 17, 18, 21, -1, 22, 23, -1, 24, 10, -1, 9, 25, 11, 8, -1, 7 };

#else // if RPI_CPU_REVISION == 0002 || RPI_CPU_REVISION == 0004 || RPI_CPU_REVISION == 0006

//                       pin  =    0   1   2  3   4  5   6  7   8   9  10  11  12  13  14  15  16  17  18  19  20  21 22  23 24  25 26
static const int pin_gpio[27] = { -1, -1, -1, 2, -1, 3, -1, 4, 14, -1, 15, 17, 18, 27, -1, 22, 23, -1, 24, 10, -1, 9, 25, 11, 8, -1, 7 };

#endif

int
main( int argc, char *args[] ) {

	// Controllo il numero minimo dei parametri
	if ( argc > 2 ) {

		// Gestore del controller gpio
		gpio io;

		// Ricavo il numero del pin scelto
		int pin;
	    char *garbage = NULL;

		// Copio il pin scelto oppure ricavo il pin della porta gpio
		if ( !strncasecmp( args[2], "pin", 3 ) ) {

			pin = (int) strtol( ( args[2] + 3 ), &garbage, 0 );

			// Processo eventuali errori
			pin = ( *garbage == '\0' && pin >= 0 && pin < 27 ) ? pin_gpio[pin] : -1;

		} else {

			pin = (int) strtol( args[2], &garbage, 0 );

			// Processo eventuali errori
			if ( *garbage != '\0' || pin < 0 || pin >= NUM_OF_PINS ) pin = -1;
		}

		// Controllo che non ci siano errori nella scelta dei pin
		if ( pin != -1 ) {

			// Modalità di un pin
			if ( !strncasecmp( args[1], "setup", 5 ) ) {

				// Estraggo la modalità del pin
				int mode = -1;

				// Controllo che sia stato passato il terzo paramentro
				if ( argc > 3 ) {

					if ( !strncasecmp( args[3], "in", 2 ) )
						mode = gpio::INPUT;
					else if ( !strncasecmp( args[3], "out", 3 ) )
						mode = gpio::OUTPUT;
				}

				// Estraggo le opzioni sul controllo pull-up/down
				int pud_mode = gpio::PUD_OFF;

				// Controllo se è stato passato il quarto paramentro opzionale
				if ( argc > 4 ) {

					if ( !strncasecmp( args[4], "pulldown", 8 ) )
						pud_mode = gpio::PULL_DOWN;
					else if ( !strncasecmp( args[4], "pullup", 6 ) )
						pud_mode = gpio::PULL_UP;
					else
						pud_mode = -1;
				}

				// Controllo che non ci siano errori nei parametri
				if ( mode != -1 && pud_mode != -1 ) {

					// Imposto la modalità del pin
					io.setup( (uint8_t) pin, (gpio::PinMode) mode );

				// Segnalo l'errore
				} else std::cerr << "Usage: " << args[0] << " setup <pin> <in|out> [pulldown|pullup]" << std::endl;

			// Scrittura su un pin di uscita
			} else if ( !strncasecmp( args[1], "write", 5 ) ) {

				// Estraggo il valore di uscita del pin
				int value = -1;

				// Controllo che sia stato passato il terzo paramentro
				if ( argc > 3 ) {

					if ( *args[3] == '0' || !strncasecmp( args[3], "low", 2 ) )
						value = gpio::LOW;
					else if ( *args[3] == '1' || !strncasecmp( args[3], "high", 3 ) )
						value = gpio::HIGH;
				}

				// Controllo che non ci siano errori nei parametri
				if ( value != -1 ) {

					// Scrivo il valore di uscita del pin
					io.write( (uint8_t) pin, value );

				// Segnalo l'errore
				} else std::cerr << "Usage: " << args[0] << " write <pin> <low|high>" << std::endl;

			// Lettura da un pin di ingresso
			} else if ( !strncasecmp( args[1], "read", 4 ) ) {

				// Scrivo a schermo il valore del pin
				std::cout << io.read( (uint8_t) pin ) << std::endl;

			// Lettura da un pin di ingresso
			} else if ( !strncasecmp( args[1], "edge", 4 ) ) {

				// Estraggo gli eventi del pin
				int events = -1;

				// Controllo che sia stato passato il terzo paramentro
				if ( argc > 3 ) {

					if ( !strncasecmp( args[3], "none", 4 ) )
						events = 0;
					else if ( !strncasecmp( args[3], "rising", 6 ) )
						events = 1;
					else if ( !strncasecmp( args[3], "falling", 7 ) )
						events = 2;
					else if ( !strncasecmp( args[3], "both", 4 ) )
						events = 3;
				}

				// Controllo che non ci siano errori nei parametri
				if ( events != -1 ) {

					// Imposto gli eventi del pin
					io.setRisingEvent( (uint8_t) pin, events == 1 || events == 3 );
					io.setFallingEvent( (uint8_t) pin, events == 2 || events == 3 );

				// Segnalo l'errore
				} else std::cerr << "Usage: " << args[0] << " edge <pin> <none|rising|falling|both>" << std::endl;

			// Segnalo l'errore nella scelta del comando
			} else std::cout << "Usage: " << args[0] << " <setup|write|read|edge> <pin|pinN> [values...]" << std::endl;

		// Segnalo l'errore nella scelta del pin/gpio
		} else std::cout << "Fatal error: invalid gpio or pin!" << std::endl;

	// Segnalo l'errore di sintassi
	} else std::cout << "Usage: " << args[0] << " <setup|write|read|edge> <pin|pinN> [values...]" << std::endl;

	return 0;
}
