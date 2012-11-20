/* 
	Title --- gpio.hpp

	Copyright (C) 2012 Giacomo Trudu - wicker25[at]gmail[dot]com

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


#ifndef _RPI_HW_GPIO_HPP_
#define _RPI_HW_GPIO_HPP_

#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>

#include <rpi-hw/rpi.hpp>

#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>
#include <rpi-hw/utils.hpp>

#define BCM2708_PERI_BASE	0x20000000
#define GPIO_BASE			(BCM2708_PERI_BASE + 0x200000)

#define	NUM_OF_PINS		54
#define	PAGE_SIZE		(4*1024)
#define BLOCK_SIZE		(4*1024)

namespace rpihw { // Begin main namespace

// I 42 registri a 32 bit del controller gpio a 54 pin 
enum Registers {

	/*
		= GPIO Function Select Registers (0 to 5) =

		The function select registers are used to define the operation of the general-purpose I/O pins.
		Each of the 54 GPIO pins uses 3 bit to select the function, therefore all registers contain
		at most 10 GPIO.

		====================GPFSEL====================
		pin	 -   9   8   7   6   5   4   3   2   1   0
		0.	xx 000 000 000 000 000 000 000 000 000 000	32 bit = 3 x 10 pin + 2 reserved
		pin	 -  19  18  17  16  15  14  13  12  11  10
		1.	xx 000 000 000 000 000 000 000 000 000 000	...
		pin	 -  29  28  27  26  25  24  23  22  21  20
		2.	xx 000 000 000 000 000 000 000 000 000 000	...
		pin	 -  39  38  37  36  35  34  33  32  31  30
		3.	xx 000 000 000 000 000 000 000 000 000 000	...
		pin	 -  49  48  47  46  45  44  43  42  41  40
		4.	xx 000 000 000 000 000 000 000 000 000 000	...
		pin	 -   -   -   -   -   -   -  53  52  51  50
		5.	xx xxx xxx xxx xxx xxx xxx 000 000 000 000	32 bit = 3 x 4 pin + 20 reserved
		==============================================

		= Codice =

		000 = GPIO pin X is an input
		001 = GPIO pin X is an output
		100 = GPIO pin X takes alternate function 0
		101 = GPIO pin X takes alternate function 1
		110 = GPIO pin X takes alternate function 2
		111 = GPIO pin X takes alternate function 3
		011 = GPIO pin X takes alternate function 4
		010 = GPIO pin X takes alternate function 5
	*/

	GPFSEL0 = 0,	// 0x 7E20 0000
	GPFSEL1 = 1,	// 0x 7E20 0004
	GPFSEL2 = 2,	// 0x 7E20 0008
	GPFSEL3 = 3,	// 0x 7E20 000C
	GPFSEL4 = 4,	// 0x 7E20 0010
	GPFSEL5 = 5,	// 0x 7E20 0014

	/*
		= GPIO Pin Output Set Registers (0 to 1) =

		=================GPSET===============
		pin	31 ...                      ... 0
		0.	 00000000000000000000000000000000	32 bit = 32 pin
		pin	        53 ...              ... 32
		1.	 xxxxxxxx000000000000000000000000	32 bit = 24 pin + 8 reserved
		=====================================

		= Codice =

		0 = No effect
		1 = Set GPIO pin X
	*/

	GPSET0 = 7,		// 0x 7E20 001C
	GPSET1 = 8,		// 0x 7E20 0020

	/*
		= GPIO Pin Output Clear Registers (0 to 1) =

		=================GPCLR===============
		pin	31 ...                      ... 0
		0.	 00000000000000000000000000000000	32 bit = 32 pin
		pin	        53 ...              ... 32
		1.	 xxxxxxxx000000000000000000000000	32 bit = 24 pin + 8 reserved
		=====================================

		= Codice =

		0 = No effect
		1 = Clear GPIO pin n
	*/

	GPCLR0 = 10,	// 0x 7E20 0028
	GPCLR1 = 11,	// 0x 7E20 002C

	/*
		= GPIO Pin Level Registers (0 to 1) =

		=================GPLEV===============
		pin	31 ...                      ... 0
		0.	 00000000000000000000000000000000	32 bit = 32 pin
		pin	        53 ...              ... 32
		1.	 xxxxxxxx000000000000000000000000	32 bit = 24 pin + 8 reserved
		=====================================

		= Codice =

		0 = GPIO pin X is low
		1 = GPIO pin X is high
	*/

	GPLEV0 = 13,	// 0x 7E20 0034
	GPLEV1 = 14,	// 0x 7E20 0038

	/*
		= GPIO Event Detect Status Registers (0 to 1) =

		=================GPEDS===============
		pin	31 ...                      ... 0
		0.	 00000000000000000000000000000000	32 bit = 32 pin
		pin	        53 ...              ... 32
		1.	 xxxxxxxx000000000000000000000000	32 bit = 24 pin + 8 reserved
		=====================================

		= Codice =

		0 = Event not detected on GPIO pin X
		1 = Event detected on GPIO pin X
	*/

	GPEDS0 = 15,	// 0x 7E20 0040
	GPEDS1 = 16,	// 0x 7E20 0044

	/*
		= GPIO Rising Edge Detect Enable Registers (0 to 1) =

		=================GPREN===============
		pin	31 ...                      ... 0
		0.	 00000000000000000000000000000000	32 bit = 32 pin
		pin	        53 ...              ... 32
		1.	 xxxxxxxx000000000000000000000000	32 bit = 24 pin + 8 reserved
		=====================================

		= Codice =

		0 = Rising edge detect disabled on GPIO pin X
		1 = Rising edge on GPIO pin X sets corresponding bit in GPEDS
	*/

	GPREN0 = 18,	// 0x 7E20 004C
	GPREN1 = 19,	// 0x 7E20 0050

	/*
		= GPIO Falling Edge Detect Enable Registers (0 to 1) =

		=================GPFEN===============
		pin	31 ...                      ... 0
		0.	 00000000000000000000000000000000	32 bit = 32 pin
		pin	        53 ...              ... 32
		1.	 xxxxxxxx000000000000000000000000	32 bit = 24 pin + 8 reserved
		=====================================

		= Codice =

		0 = Falling edge detect disabled on GPIO pin X
		1 = Falling edge on GPIO pin X sets corresponding bit in GPEDS
	*/

	GPFEN0 = 21,	// 0x 7E20 0058
	GPFEN1 = 22,	// 0x 7E20 005C

	/*
		= GPIO High Detect Enable Registers (0 to 1) =

		=================GPHEN===============
		pin	31 ...                      ... 0
		0.	 00000000000000000000000000000000	32 bit = 32 pin
		pin	        53 ...              ... 32
		1.	 xxxxxxxx000000000000000000000000	32 bit = 24 pin + 8 reserved
		=====================================

		= Codice =

		0 = High detect disabled on GPIO pin X
		1 = High on GPIO pin n sets corresponding bit in GPEDS
	*/

	GPHEN0 = 24,	// 0x 7E20 0064
	GPHEN1 = 25,	// 0x 7E20 0068

	/*
		= GPIO Low Detect Enable Registers (0 to 1) =

		=================GPLEN===============
		pin	31 ...                      ... 0
		0.	 00000000000000000000000000000000	32 bit = 32 pin
		pin	        53 ...              ... 32
		1.	 xxxxxxxx000000000000000000000000	32 bit = 24 pin + 8 reserved
		=====================================

		= Codice =

		0 = Low detect disabled on GPIO pin X
		1 = Low on GPIO pin n sets corresponding bit in GPEDS
	*/

	GPLEN0 = 27,	// 0x 7E20 0070
	GPLEN1 = 28,	// 0x 7E20 0074

	/*
		= GPIO Pull-up/down Register =

		=================GPPUD===============
		0.	 xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx00	32 bit = 2 control bits + 8 reserved
		=====================================

		= Codice =

		00 = Disable pull-up/down
		01 = Enable pull-down control
		10 = Enable pull-up control
		11 = Reserved
	*/

	GPPUD0 = 37,	// 0x 7E20 0094

	/*
		= GPIO Pull-up/down Clock Registers (0 to 1) =

		The GPIO Pull-up/down Clock Registers control the actuation of internal pull-downs on
		the respective GPIO pins.
		These registers must be used in conjunction with the GPPUD register to effect
		GPIO Pull-up/down changes. The following sequence of events is required:

		1. Write to GPPUD to set the required control signal
		2. Wait 150 cycles – this provides the required set-up time for the control signal
		3. Write to GPPUDCLK0/1 to clock the control signal into the GPIO pads you wish to modify
		4. Wait 150 cycles – this provides the required hold time for the control signal
		5. Write to GPPUD to remove the control signal
		6. Write to GPPUDCLK0/1 to remove the clock

		===============GPPUDCLK==============
		pin	31 ...                      ... 0
		0.	 00000000000000000000000000000000	32 bit = 32 pin
		pin	        53 ...              ... 32
		1.	 xxxxxxxx000000000000000000000000	32 bit = 24 pin + 8 reserved
		=====================================

		= Codice =

		0 = No effect
		1 = Assert clock on line X
	*/

	GPPUDCLK0 = 38,	// 0x 7E20 0098
	GPPUDCLK1 = 39	// 0x 7E20 009C
};


/* GPIO CONTROLLER INTERFACE */
class gpio {

public:

	// Raspberry Pi pins
	enum RpiPins {

	#if RPI_REVISION == 0002 || RPI_REVISION == 0003

		PIN3	= 0,	PIN5	= 1,	PIN7	= 4,
		PIN8	= 14,	PIN10	= 15,	PIN11	= 17,
		PIN12	= 18,	PIN13	= 21,	PIN15	= 22,
		PIN16	= 23,	PIN18	= 24,	PIN19	= 10,
		PIN21	= 9,	PIN22	= 25,	PIN23	= 11,
		PIN24	= 8,	PIN26	= 7

	#else // if RPI_REVISION == 0002 || RPI_REVISION == 0004 || RPI_REVISION == 0006

		PIN3	= 2,	PIN5	= 3,	PIN7	= 4,
		PIN8	= 14,	PIN10	= 15,	PIN11	= 17,
		PIN12	= 18,	PIN13	= 27,	PIN15	= 22,
		PIN16	= 23,	PIN18	= 24,	PIN19	= 10,
		PIN21	= 9,	PIN22	= 25,	PIN23	= 11,
		PIN24	= 8,	PIN26	= 7

	#endif

	};

	// GPIO constants
	enum Level { LOW = 0, HIGH = 1 };
	enum PinMode { INPUT = 0, OUTPUT = 1 };
	enum PullMode { PUD_OFF = 0, PULL_DOWN = 1, PULL_UP = 2 };

	// Constructor and destructor methods
	gpio();
	virtual ~gpio();

	// Sets a GPIO pin
	void setup( uint8_t pin, PinMode mode, PullMode pud_mode = PUD_OFF );
	// Sets the value of a output pin
	void write( uint8_t pin, bool value );
	// Returns the value of a input pin
	bool read( uint8_t pin ) const;
	// Returns event state of a GPIO pin
	bool checkEvent( uint8_t pin ) const;
	// Enables/disables rising edge event on a GPIO pin
	void setRisingEvent( uint8_t pin, bool enabled );
	// Enables/disables falling edge event on a GPIO pin
	void setFallingEvent( uint8_t pin, bool enabled );
	// Enables/disables high event on a GPIO pin
	void setHighEvent( uint8_t pin, bool enabled );
	// Enables/disables low event on a GPIO pin
	void setLowEvent( uint8_t pin, bool enabled );
	// Enables/disables pull-up/down control on a GPIO pin
	void setPullUpDown( uint8_t pin, PullMode mode );

private:

	// File descriptor of `/dev/mem`
	int m_mem_fd;

	// Memory mapped of GPIO controller
	uint32_t *m_map;

	// GPIO controller virtual address
	volatile uint32_t *m_addr;

	// Sets a bit value on one of the GPIO controller registers
	void setBit( uint8_t offset, uint8_t index, bool value );
	// Returns a bit value from one of the GPIO controller registers
	bool getBit( uint8_t offset, uint8_t index ) const;

	// Wait some cycles
	void waitCycles( size_t cycles ) const;

	// Print a GPIO controller register (debug function)
	void print_register( uint8_t offset, uint8_t group_bits = 0 ) const;
};

} // End of main namespace

#endif
