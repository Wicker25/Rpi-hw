/* 
	Title --- driver/bcm2835.hpp

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


#ifndef _RPI_HW_IFACE_BCM2835_HPP_
#define _RPI_HW_IFACE_BCM2835_HPP_

#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#include <rpi-hw/rpi.hpp>

#include <rpi-hw/consts.hpp>
#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>
#include <rpi-hw/utils.hpp>

#define BCM2708_PERI_BASE	0x20000000

#define CLOCK_BASE			(BCM2708_PERI_BASE + 0x00101000)
#define GPIO_BASE			(BCM2708_PERI_BASE + 0x00200000)
#define GPIO_PWM			(BCM2708_PERI_BASE + 0x0020C000)

#define	NUM_OF_PINS		54
#define	PAGE_SIZE		(4*1024)
#define BLOCK_SIZE		(4*1024)

namespace rpihw { // Begin main namespace

/*!
	@namespace rpihw::driver
	@brief Namespace of the main driver.
*/

namespace driver { // Begin drivers namespace

/*!
	@class bcm2835
	@brief Broadcom BCM2835 controller.
*/
class bcm2835 {

public:

	//! BCM2708 registers.
	enum Registers {

		/* ================== GPIO Controller registers ================== */

		/*!
			@section title GPIO Function Select Registers (0 to 5)

			The function select registers are used to define the operation of the general-purpose I/O pins.
			Each of the 54 GPIO pins uses 3 bit to select the function, therefore all registers contain
			at most 10 GPIO.

			@code
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
			@endcode

			@section code Codes

			@li 000 = GPIO pin X is an input
			@li 001 = GPIO pin X is an output
			@li 100 = GPIO pin X takes alternate function 0
			@li 101 = GPIO pin X takes alternate function 1
			@li 110 = GPIO pin X takes alternate function 2
			@li 111 = GPIO pin X takes alternate function 3
			@li 011 = GPIO pin X takes alternate function 4
			@li 010 = GPIO pin X takes alternate function 5
		*/

		GPFSEL0 = 0,	// 0x 7E20 0000
		GPFSEL1 = 1,	// 0x 7E20 0004
		GPFSEL2 = 2,	// 0x 7E20 0008
		GPFSEL3 = 3,	// 0x 7E20 000C
		GPFSEL4 = 4,	// 0x 7E20 0010
		GPFSEL5 = 5,	// 0x 7E20 0014

		/*!
			@section title GPIO Pin Output Set Registers (0 to 1)

			@code
			=================GPSET===============
			pin	31 ...                      ... 0
			0.	 00000000000000000000000000000000	32 bit = 32 pin
			pin	        53 ...              ... 32
			1.	 xxxxxxxx000000000000000000000000	32 bit = 24 pin + 8 reserved
			=====================================
			@endcode

			@section Codes

			@li 0 = No effect
			@li 1 = Set GPIO pin X
		*/

		GPSET0 = 7,		// 0x 7E20 001C
		GPSET1 = 8,		// 0x 7E20 0020

		/*!
			@section title GPIO Pin Output Clear Registers (0 to 1)

			@code
			=================GPCLR===============
			pin	31 ...                      ... 0
			0.	 00000000000000000000000000000000	32 bit = 32 pin
			pin	        53 ...              ... 32
			1.	 xxxxxxxx000000000000000000000000	32 bit = 24 pin + 8 reserved
			=====================================
			@endcode

			@section code Codes

			@li 0 = No effect
			@li 1 = Clear GPIO pin n
		*/

		GPCLR0 = 10,	// 0x 7E20 0028
		GPCLR1 = 11,	// 0x 7E20 002C

		/*!
			@section title GPIO Pin Level Registers (0 to 1)

			@code
			=================GPLEV===============
			pin	31 ...                      ... 0
			0.	 00000000000000000000000000000000	32 bit = 32 pin
			pin	        53 ...              ... 32
			1.	 xxxxxxxx000000000000000000000000	32 bit = 24 pin + 8 reserved
			=====================================
			@endcode

			@section code Codes

			@li 0 = GPIO pin X is low
			@li 1 = GPIO pin X is high
		*/

		GPLEV0 = 13,	// 0x 7E20 0034
		GPLEV1 = 14,	// 0x 7E20 0038

		/*!
			@section title GPIO Event Detect Status Registers (0 to 1)

			@code
			=================GPEDS===============
			pin	31 ...                      ... 0
			0.	 00000000000000000000000000000000	32 bit = 32 pin
			pin	        53 ...              ... 32
			1.	 xxxxxxxx000000000000000000000000	32 bit = 24 pin + 8 reserved
			=====================================
			@endcode

			@section code Codes

			@li 0 = Event not detected on GPIO pin X
			@li 1 = Event detected on GPIO pin X
		*/

		GPEDS0 = 15,	// 0x 7E20 0040
		GPEDS1 = 16,	// 0x 7E20 0044

		/*!
			@section title GPIO Rising Edge Detect Enable Registers (0 to 1)

			@code
			=================GPREN===============
			pin	31 ...                      ... 0
			0.	 00000000000000000000000000000000	32 bit = 32 pin
			pin	        53 ...              ... 32
			1.	 xxxxxxxx000000000000000000000000	32 bit = 24 pin + 8 reserved
			=====================================
			@endcode

			@section code Codes

			@li 0 = Rising edge detect disabled on GPIO pin X
			@li 1 = Rising edge on GPIO pin X sets corresponding bit in GPEDS
		*/

		GPREN0 = 18,	// 0x 7E20 004C
		GPREN1 = 19,	// 0x 7E20 0050

		/*!
			@section title GPIO Falling Edge Detect Enable Registers (0 to 1)

			@code
			=================GPFEN===============
			pin	31 ...                      ... 0
			0.	 00000000000000000000000000000000	32 bit = 32 pin
			pin	        53 ...              ... 32
			1.	 xxxxxxxx000000000000000000000000	32 bit = 24 pin + 8 reserved
			=====================================
			@endcode

			@section code Codes

			@li 0 = Falling edge detect disabled on GPIO pin X
			@li 1 = Falling edge on GPIO pin X sets corresponding bit in GPEDS
		*/

		GPFEN0 = 21,	// 0x 7E20 0058
		GPFEN1 = 22,	// 0x 7E20 005C

		/*!
			@section title GPIO High Detect Enable Registers (0 to 1)

			@code
			=================GPHEN===============
			pin	31 ...                      ... 0
			0.	 00000000000000000000000000000000	32 bit = 32 pin
			pin	        53 ...              ... 32
			1.	 xxxxxxxx000000000000000000000000	32 bit = 24 pin + 8 reserved
			=====================================
			@endcode

			@section code Codes

			@li 0 = High detect disabled on GPIO pin X
			@li 1 = High on GPIO pin n sets corresponding bit in GPEDS
		*/

		GPHEN0 = 24,	// 0x 7E20 0064
		GPHEN1 = 25,	// 0x 7E20 0068

		/*!
			@section title GPIO Low Detect Enable Registers (0 to 1)

			@code
			=================GPLEN===============
			pin	31 ...                      ... 0
			0.	 00000000000000000000000000000000	32 bit = 32 pin
			pin	        53 ...              ... 32
			1.	 xxxxxxxx000000000000000000000000	32 bit = 24 pin + 8 reserved
			=====================================
			@endcode

			@section code Codes

			@li 0 = Low detect disabled on GPIO pin X
			@li 1 = Low on GPIO pin n sets corresponding bit in GPEDS
		*/

		GPLEN0 = 27,	// 0x 7E20 0070
		GPLEN1 = 28,	// 0x 7E20 0074

		/*!
			@section title GPIO Pull-up/down Register

			@code
			=================GPPUD===============
			0.	 xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx00	32 bit = 2 control bits + 8 reserved
			=====================================
			@endcode

			@section code Codes

			@li 00 = Disable pull-up/down
			@li 01 = Enable pull-down control
			@li 10 = Enable pull-up control
			@li 11 = Reserved
		*/

		GPPUD0 = 37,	// 0x 7E20 0094

		/*!
			@section title GPIO Pull-up/down Clock Registers (0 to 1)

			The GPIO Pull-up/down Clock Registers control the actuation of internal pull-downs on
			the respective GPIO pins.
			These registers must be used in conjunction with the GPPUD register to effect
			GPIO Pull-up/down changes. The following sequence of events is required:

			-# Write to GPPUD to set the required control signal
			-# Wait 150 cycles – this provides the required set-up time for the control signal
			-# Write to GPPUDCLK0/1 to clock the control signal into the GPIO pads you wish to modify
			-# Wait 150 cycles – this provides the required hold time for the control signal
			-# Write to GPPUD to remove the control signal
			-# Write to GPPUDCLK0/1 to remove the clock

			@code
			===============GPPUDCLK==============
			pin	31 ...                      ... 0
			0.	 00000000000000000000000000000000	32 bit = 32 pin
			pin	        53 ...              ... 32
			1.	 xxxxxxxx000000000000000000000000	32 bit = 24 pin + 8 reserved
			=====================================
			@endcode

			@section code Codes

			@li 0 = No effect
			@li 1 = Assert clock on line X
		*/

		GPPUDCLK0 = 38,	// 0x 7E20 0098
		GPPUDCLK1 = 39,	// 0x 7E20 009C


		/** ================== PWM Controller registers ================== **/

		/*!
			@section title PWM Control

			@code
			==================CTL================
			     xxxxxxxxxxxxxxxxx0x0000000000000	32 bit = 14 fields + 18 reserved
			=====================================
			@endcode

			@section title CTL Register

			@code
			   Bit     Field name        Description
			=================================================================
			    15          MSEN2        Channel 2 M/S enable
			                               0 = PWM algorithm is used
			                               1 = M/S transmission is used
			-----------------------------------------------------------------
			    13          USEF2        Channel 2 use FIFO
			                               0 = Data register is transmitted
			                               1 = Fifo is used for transmission
			-----------------------------------------------------------------
			    12          POLA2        Channel 2 polarity
			                               0 = 0->low 1->high
			                               1 = 0->high 1->low
			-----------------------------------------------------------------
			    11          SBIT2        Channel 2 silence bit
			                             Defines the state of the output
			                             when no transmission takes place.
			-----------------------------------------------------------------
			    10          RPTL2        Channel 2 repeat last data
			                               0 = Transmission interrupts when
			                                   FIFO is empty
			                               1 = Last data in FIFO is
			                                   transmitted repetedly until
			                                   FIFO is not empty
			-----------------------------------------------------------------
			     9          MODE2        Channel 2 mode
			                               0 = PWM mode
			                               1 = Serialiser mode
			-----------------------------------------------------------------
			     8          PWEN2        Channel 2 enable
			                               0 = Channel is disabled
			                               1 = Channel is enabled
			-----------------------------------------------------------------
			     7          MSEN1        Channel 1 M/S enable
			                               0 = PWM algorithm is used
			                               1 = M/S transmission is used
			-----------------------------------------------------------------
			     6          CLRF1        Clear FIFO
			                               0 = Clears FIFO
			                               1 = Has no effect
			                             This is a single shot operation.
			                             This bit always reads 0.
			-----------------------------------------------------------------
			     5          USEF1        Channel 1 use FIFO
			                               0 = Data register is transmitted
			                               1 = Fifo is used for transmission
			-----------------------------------------------------------------
			     4          POLA1        Channel 1 use FIFO
			                               0 = 0->low 1->high
			                               1 = 0->high 1->low
			-----------------------------------------------------------------
			     3          SBIT1        Channel 1 silence bit
			                             Defines the state of the output
			                             when no transmission takes place.
			-----------------------------------------------------------------
			     2          RPTL1        Channel 1 repeat last data
			                               0 = Transmission interrupts when
			                                   FIFO is empty
			                               1 = Last data in FIFO is
			                                   transmitted repetedly until
			                                   FIFO is not empty
			-----------------------------------------------------------------
			     1          MODE1        Channel 1 mode
			                               0 = PWM mode
			                               1 = Serialiser mode
			-----------------------------------------------------------------
			     0          PWEN1        Channel 1 enable
			                               0 = Channel is disabled
			                               1 = Channel is enabled
			=================================================================
			@endcode
		*/

		PWM_CTL = 1,	// 0x 7E20 C000

		/*!
			@section title PWM Status

			@code
			==================STA================
			     xxxxxxxxxxxxxxxxxxxx000000000000	32 bit = 12 fields + 20 reserved
			=====================================
			@endcode

			@section title STA Register

			@code
			   Bit     Field name        Description
			=============================================================
			    12           STA4        Channel 4 state
			    11           STA3        Channel 3 state
			    10           STA2        Channel 2 state
			     9           STA1        Channel 1 state
			     8           BERR        Bus error flag
			     7          GAPO4        Channel 4 gap cccurred flag
			     6          GAPO3        Channel 3 gap cccurred flag
			     5          GAPO2        Channel 2 gap cccurred flag
			     4          GAPO1        Channel 1 gap cccurred flag
			     3          RERR1        FIFO read error flag
			     2          WERR1        FIFO write error flag
			     1          EMPT1        FIFO empty flag
			     0          FULL1        FIFO full flag
			=============================================================
			@endcode
		*/

		PWM_STA = 2,	// 0x 7E20 C004

		/*!
			@section title DMAC Register

			@code
			=================DMAC================
			     0xxxxxxxxxxxxxxxx000000000000000	32 bit = 16 fields + 16 reserved
			=====================================
			@endcode

			@section title DMAC Register

			@code
			   Bit     Field name        Description
			=============================================================
			   31            ENAB        DMA Enable
			 15:8           PANIC        DMA Threshold for PANIC signal
			  7:0            DREQ        DMA Threshold for DREQ signal
			=============================================================
			@endcode
		*/

		PWM_DMAC = 3,	// 0x 7E20 C008

		/*!
			@section title PWM Channel 1 Range

			@code
			=================RNG1================
			0.	 00000000000000000000000000000000	32 bit = 32 fields
			=====================================
			@endcode
		*/

		PWM_RNG1 = 4,	// 0x 7E20 C010

		/*!
			@section title PWM Channel 1 Data

			@code
			=================DAT1================
			0.	 00000000000000000000000000000000	32 bit = 32 fields
			=====================================
			@endcode
		*/

		PWM_DAT1 = 5,	// 0x 7E20 C014

		/*!
			@section title PWM FIFO Input

			@code
			=================FIF1================
			0.	 00000000000000000000000000000000	32 bit = 32 fields
			=====================================
			@endcode
		*/

		PWM_FIF1 = 6,	// 0x 7E20 C018

		/*!
			@section title PWM Channel 2 Range

			@code
			=================RNG2================
			0.	 00000000000000000000000000000000	32 bit = 32 fields
			=====================================
			@endcode
		*/

		PWM_RNG2 = 7,	// 0x 7E20 C020

		/*!
			@section title PWM Channel 2 Data

			@code
			=================DAT2================
			0.	 00000000000000000000000000000000	32 bit = 32 fields
			=====================================
			@endcode
		*/

		PWM_DAT2 = 8	// 0x 7E20 C024
	};


	//! Raspberry Pi pins.
	enum RpiPins {

	#if RPI_REVISION == 0x0002 || RPI_REVISION == 0x0003

		PIN3	= 0,	PIN5	= 1,	PIN7	= 4,
		PIN8	= 14,	PIN10	= 15,	PIN11	= 17,
		PIN12	= 18,	PIN13	= 21,	PIN15	= 22,
		PIN16	= 23,	PIN18	= 24,	PIN19	= 10,
		PIN21	= 9,	PIN22	= 25,	PIN23	= 11,
		PIN24	= 8,	PIN26	= 7

	#else

		PIN3	= 2,	PIN5	= 3,	PIN7	= 4,
		PIN8	= 14,	PIN10	= 15,	PIN11	= 17,
		PIN12	= 18,	PIN13	= 27,	PIN15	= 22,
		PIN16	= 23,	PIN18	= 24,	PIN19	= 10,
		PIN21	= 9,	PIN22	= 25,	PIN23	= 11,
		PIN24	= 8,	PIN26	= 7

	#endif

	};

	//! Constructor method.
	bcm2835();

	//! Destructor method.
	virtual ~bcm2835();

	/*!
		@brief Sets the mode of a GPIO pin.
		@param[in] pin The GPIO pin.
		@param[in] mode The GPIO mode.
		@param[in] pud_mode The pull resistor mode.
	*/
	void setup( uint8_t pin, uint8_t mode, uint8_t pud_mode = PUD_OFF );

	/*!
		@brief Sets the value of a output pin.
		@param[in] pin The output pin.
		@param[in] value The value of output pin.
	*/
	void write( uint8_t pin, bool value );

	/*!
		@brief Returns the value of a input pin.
		@param[in] pin The input pin.
		@return The value of input pin.
	*/
	bool read( uint8_t pin ) const;

	/*!
		@brief Returns the event state of a GPIO pin.
		@param[in] pin The GPIO pin.
		@return The event state.
	*/
	bool checkEvent( uint8_t pin ) const;

	/*!
		@brief Enables/disables the rising edge event on a GPIO pin.
		@param[in] pin The GPIO pin.
		@param[in] enabled If \c true enable the rising edge event.
	*/
	void setRisingEvent( uint8_t pin, bool enabled );

	/*!
		@brief Enables/disables the falling edge event on a GPIO pin.
		@param[in] pin The GPIO pin.
		@param[in] enabled If \c true enable the falling edge event.
	*/
	void setFallingEvent( uint8_t pin, bool enabled );

	/*!
		@brief Enables/disables the high event on a GPIO pin.
		@param[in] pin The GPIO pin.
		@param[in] enabled If \c true enable the high event.
	*/
	void setHighEvent( uint8_t pin, bool enabled );

	/*!
		@brief Enables/disables the low event on a GPIO pin.
		@param[in] pin The GPIO pin.
		@param[in] enabled If \c true enable the low event.
	*/
	void setLowEvent( uint8_t pin, bool enabled );

	/*!
		@brief Enables/disables the pull-up/down control on a GPIO pin.
		@param[in] pin The GPIO pin.
		@param[in] mode The pull resistor mode.
	*/
	void setPullUpDown( uint8_t pin, uint8_t mode );

private:

	//! File descriptor of `/dev/mem`.
	int m_mem_fd;

	//! GPIO controller virtual address.
	volatile uint32_t *m_gpio;

	//! PWM controller virtual address.
	volatile uint32_t *m_pwm;

	/*!
		@brief Sets a bit value on one of the GPIO controller registers.
		@param[in] offset The register offset.
		@param[in] index The bit position.
		@param[in] value The bit value.
	*/
	void setBit( uint8_t offset, uint8_t index, bool value );

	/*!
		@brief Returns a bit value from one of the GPIO controller registers.
		@param[in] offset The register offset.
		@param[in] index The bit position.
		@return The bit value.
	*/
	bool getBit( uint8_t offset, uint8_t index ) const;

	/*!
		@brief Wait some CPU cycles.
		@param[in] cycles Number of CPU cycles.
	*/
	void waitCycles( size_t cycles ) const;
};

} // End of drivers namespace

} // End of main namespace


// Include inline methods 
#include <rpi-hw/driver/bcm2835-inl.hpp>

#endif /* _RPI_HW_IFACE_BCM2835_HPP_ */
