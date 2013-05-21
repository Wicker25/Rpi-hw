/* 
    Title --- rpi-gpio.cpp [tools]

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


#include <iostream>
#include <cstdlib>
#include <cstring>

#include <rpi-hw.hpp>
#include <rpi-hw/gpio.hpp>

// Constants
#define RPI_GPIO_VERSION	"0.2"

static const char *usage =
"Usage: rpi-gpio <set|write|event|write|read> <gpio> [options]\n\n"
"       rpi-gpio set   <gpio> <in|out|pulldown|pullup|pudoff>\n"
"       rpi-gpio write <gpio> <high|low>\n"
"       rpi-gpio event <gpio> <rising|falling|high|low> <enabled|disabled>\n"
"       rpi-gpio event <gpio>\n"
"       rpi-gpio read  <gpio>\n"
"       rpi-gpio -h\n"
"       rpi-gpio -v\n";


// Raspberry Pi pins
#if RPI_REVISION == 0x0002 || RPI_REVISION == 0x0003

//                       pin  =    0   1   2   3   4   5   6   7   8   9  10  11  12  13
static const int pin_gpio[27] = { -1, -1, -1,  0, -1,  1, -1,  4, 14, -1, 15, 17, 18, 21,
//								  14  15  16  17  18  19  20  21 22  23  24  25  26
								  -1, 22, 23, -1, 24, 10, -1, 9, 25, 11,  8, -1,  7 };

#else

//                       pin  =    0   1   2  3   4   5   6   7   8   9  10  11  12  13
static const int pin_gpio[27] = { -1, -1, -1, 2, -1,  3, -1,  4, 14, -1, 15, 17, 18, 27,
//								  14  15  16  17  18  19  20  21  22  23  24  25  26
								  -1, 22, 23, -1, 24, 10, -1,  9, 25, 11,  8, -1,  7 };
#endif


// Use the Rpi-hw namespace
using namespace rpihw;

int
main( int argc, char *args[] ) {

	// Control flag
	bool success = false;

	// Check minimum number of arguments
	if ( argc > 2 ) {

		// GPIO control interface
		gpio io;

		// Get selected GPIO pin
	    char *garbage = NULL;
		int pin;

		if ( !strncasecmp( args[2], "pin", 3 ) ) {

			pin = (int) strtol( ( args[2] + 3 ), &garbage, 0 );
			pin = ( *garbage == '\0' && pin >= 0 && pin < 27 ) ? pin_gpio[pin] : -1;

		} else {

			pin = (int) strtol( args[2], &garbage, 0 );
			if ( *garbage != '\0' || pin >= NUM_OF_PINS ) pin = -1;
		}

		// Check if there are no errors
		if ( pin != -1 ) {

			// Set GPIO pin mode
			if ( !strcasecmp( args[1], "set" ) ) {

				if ( argc > 3 ) {

					// Input mode
					if ( !strcasecmp( args[3], "in" ) || !strcasecmp( args[3], "input" ) ) {

						io.setup( (uint8_t) pin, gpio::INPUT );
						success = true;

					// Output mode
					} else if ( !strcasecmp( args[3], "out" ) || !strcasecmp( args[3], "output" ) ) {

						io.setup( (uint8_t) pin, gpio::OUTPUT );
						success = true;

					// Pull-down control
					} else if ( !strcasecmp( args[3], "pulldown" ) ) {

						io.setPullUpDown( (uint8_t) pin, gpio::PULL_DOWN );
						success = true;

					// Pull-up control
					} else if ( !strcasecmp( args[3], "pullup" ) ) {

						io.setPullUpDown( (uint8_t) pin, gpio::PULL_UP );
						success = true;

					// Disable pull-up/down control
					} else if ( !strcasecmp( args[3], "pudoff" ) ) {

						io.setPullUpDown( (uint8_t) pin, gpio::PUD_OFF );
						success = true;
					}
				}

			// Set events
			} else if ( !strcasecmp( args[1], "event" ) ) {

				if ( argc > 3 ) {

					if ( argc > 4 ) {

						// Get selected mode
						int mode = -1;

						if ( !strcasecmp( args[4], "enabled" ) )
							mode = 1;
						else if ( !strcasecmp( args[4], "disabled" ) )
							mode = 0;

						// Check if there are no errors
						if ( mode != -1 ) {

							// Rising edge event
							if ( !strcasecmp( args[3], "rising" ) ) {

								io.setRisingEvent( (uint8_t) pin, (bool) mode );
								success = true;

							// Falling edge event
							} else if ( !strcasecmp( args[3], "falling" ) ) {

								io.setFallingEvent( (uint8_t) pin, (bool) mode );
								success = true;

							// High event
							} else if ( !strcasecmp( args[3], "high" ) ) {

								io.setHighEvent( (uint8_t) pin, (bool) mode );
								success = true;

							// Low event
							} else if ( !strcasecmp( args[3], "low" ) ) {

								io.setLowEvent( (uint8_t) pin, (bool) mode );
								success = true;
							}
						}
					}

				// Otherwise, detect events 
				} else {

					std::cout << io.checkEvent( (uint8_t) pin ) << std::endl;
					success = true;
				}

			// Write on output pin
			} else if ( !strcasecmp( args[1], "write" ) ) {

				// Get the value of the output pin
				int value = -1;

				if ( argc > 3 ) {

					if ( *args[3] == '0' || !strcasecmp( args[3], "low" ) )
						value = gpio::LOW;
					else if ( *args[3] == '1' || !strcasecmp( args[3], "high" ) )
						value = gpio::HIGH;
				}

				// Check if there are errors
				if ( value != -1 ) {

					// Write the value on the GPIO controller interface
					io.write( (uint8_t) pin, value );
					success = true;
				}

			// Read from input pin
			} else if ( !strcasecmp( args[1], "read" ) ) {

				// Read the value from the GPIO controller interface
				std::cout << io.read( (uint8_t) pin ) << std::endl;
				success = true;
			}
		}
	}

	if ( argc > 1 ) {

		// Print `rpi-gpio` version
		if ( !strcasecmp( args[1], "-v" ) ) {

			std::cout << "rpi-gpio v" << RPI_GPIO_VERSION << " by Giacomo Trudu aka `Wicker25`" << std::endl;
			success = true;

		// Print helps
		} else if ( !strcasecmp( args[1], "-h" ) ) {

			std::cout << usage << std::endl;
			success = true;
		}
	}

	// Handle other error
	if ( !success ) {

		std::cout << usage << std::endl;
	}

	return 0;
}
