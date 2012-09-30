/* 
	Title --- gpio.hpp

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

#ifndef _RPI_HW_GPIO_HPP_
#define _RPI_HW_GPIO_HPP_

#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>

#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>

#define BCM2708_PERI_BASE	0x20000000
#define GPIO_BASE			(BCM2708_PERI_BASE + 0x200000)

#define	NUM_OF_PINS		54
#define	PAGE_SIZE		(4*1024)
#define BLOCK_SIZE		(4*1024)

namespace rpihw { // Namespace di Rpi-hw

// I 42 registri a 32 bit del controller gpio a 54 pin 
enum {

	/*
		= I 6 registri di selezione della funzione (da 0 a 5) =

		Ogni registro controlla lo stato di 10 pin, codificato in 3 bit di memoria.
		Poiché il numero totale dei pin è 54, l'ultimo registro gestisce solo 4 pin.

		====================GPFSEL====================
		pin	 -   9   8   7   6   5   4   3   2   1   0
		0.	xx 000 000 000 000 000 000 000 000 000 000	32 bit = 3 x 10 pin + 2 inutilizzati
		pin	 -  19  18  17  16  15  14  13  12  11  10
		1.	xx 000 000 000 000 000 000 000 000 000 000	...
		pin	 -  29  28  27  26  25  24  23  22  21  20
		2.	xx 000 000 000 000 000 000 000 000 000 000	...
		pin	 -  39  38  37  36  35  34  33  32  31  30
		3.	xx 000 000 000 000 000 000 000 000 000 000	...
		pin	 -  49  48  47  46  45  44  43  42  41  40
		4.	xx 000 000 000 000 000 000 000 000 000 000	...
		pin	 -   -   -   -   -   -   -  53  52  51  50
		5.	xx xxx xxx xxx xxx xxx xxx 000 000 000 000	32 bit = 3 x 4 pin + 20 inutilizzati
		==============================================

		= Codice =

		000 = il pin X è un input
		001 = il pin X è un output
		100 = il pin X usa la funzione alternativa 0
		101 = il pin X usa la funzione alternativa 1
		110 = il pin X usa la funzione alternativa 2
		111 = il pin X usa la funzione alternativa 3
		011 = il pin X usa la funzione alternativa 4
		010 = il pin X usa la funzione alternativa 5
	*/

	GPFSEL0 = 0,	// 0x 7E20 0000
	GPFSEL1 = 1,	// 0x 7E20 0004
	GPFSEL2 = 2,	// 0x 7E20 0008
	GPFSEL3 = 3,	// 0x 7E20 000C
	GPFSEL4 = 4,	// 0x 7E20 0010
	GPFSEL5 = 5,	// 0x 7E20 0014

	/*
		= I 2 registri per l'impostazione delle uscite (da 0 a 1) =

		=================GPSET===============
		pin	31 ...                      ... 0
		0.	 00000000000000000000000000000000	32 bit = 32 pin
		pin	        53 ...              ... 32
		1.	 xxxxxxxx000000000000000000000000	32 bit = 24 pin + 8 inutilizzati
		=====================================

		= Codice =

		0 = Nessun effetto sul pin X
		1 = Imposta il pin X
	*/

	GPSET0 = 7,		// 0x 7E20 001C
	GPSET1 = 8,		// 0x 7E20 0020

	/*
		= I 2 registri per la pulitura delle uscite (da 0 a 1) =

		=================GPCLR===============
		pin	31 ...                      ... 0
		0.	 00000000000000000000000000000000	32 bit = 32 pin
		pin	        53 ...              ... 32
		1.	 xxxxxxxx000000000000000000000000	32 bit = 24 pin + 8 inutilizzati
		=====================================

		= Codice =

		0 = Nessun effetto sul pin X
		1 = Pulisce il pin X
	*/

	GPCLR0 = 10,	// 0x 7E20 0028
	GPCLR1 = 11,	// 0x 7E20 002C

	/*
		= I 2 registri del livello dei pin di ingresso (da 0 a 1) =

		=================GPLEV===============
		pin	31 ...                      ... 0
		0.	 00000000000000000000000000000000	32 bit = 32 pin
		pin	        53 ...              ... 32
		1.	 xxxxxxxx000000000000000000000000	32 bit = 24 pin + 8 inutilizzati
		=====================================

		= Codice =

		0 = Il pin X è low
		1 = Il pin X è high
	*/

	GPLEV0 = 13,	// 0x 7E20 0034
	GPLEV1 = 14,	// 0x 7E20 0038

	/*
		= I 2 registri per l'individuazione degli eventi (da 0 a 1) =

		=================GPEDS===============
		pin	31 ...                      ... 0
		0.	 00000000000000000000000000000000	32 bit = 32 pin
		pin	        53 ...              ... 32
		1.	 xxxxxxxx000000000000000000000000	32 bit = 24 pin + 8 inutilizzati
		=====================================

		= Codice =

		0 = Nessun evento rilevato sul pin X
		1 = Evento rilevato sul pin X
	*/

	GPEDS0 = 15,	// 0x 7E20 0040
	GPEDS1 = 16,	// 0x 7E20 0044

	/*
		= I 2 registri per l'abilitazione dell'evento di "risalita" del segnale (da 0 a 1) =

		=================GPREN===============
		pin	31 ...                      ... 0
		0.	 00000000000000000000000000000000	32 bit = 32 pin
		pin	        53 ...              ... 32
		1.	 xxxxxxxx000000000000000000000000	32 bit = 24 pin + 8 inutilizzati
		=====================================

		= Codice =

		0 = Il pin X non è abilitato per l'individuazione
		1 = Il pin X è abilitato per l'individuazione
	*/

	GPREN0 = 18,	// 0x 7E20 004C
	GPREN1 = 19,	// 0x 7E20 0050

	/*
		= I 2 registri per l'abilitazione dell'evento di "caduta" del segnale (da 0 a 1) =

		=================GPFEN===============
		pin	31 ...                      ... 0
		0.	 00000000000000000000000000000000	32 bit = 32 pin
		pin	        53 ...              ... 32
		1.	 xxxxxxxx000000000000000000000000	32 bit = 24 pin + 8 inutilizzati
		=====================================

		= Codice =

		0 = Il pin X non è abilitato per l'individuazione
		1 = Il pin X è abilitato per l'individuazione
	*/

	GPFEN0 = 21,	// 0x 7E20 0058
	GPFEN1 = 22,	// 0x 7E20 005C

	/*
		= I 2 registri per l'abilitazione dell'evento del segnale "alto" (da 0 a 1) =

		=================GPHEN===============
		pin	31 ...                      ... 0
		0.	 00000000000000000000000000000000	32 bit = 32 pin
		pin	        53 ...              ... 32
		1.	 xxxxxxxx000000000000000000000000	32 bit = 24 pin + 8 inutilizzati
		=====================================

		= Codice =

		0 = Il pin X non è abilitato per l'individuazione
		1 = Il pin X è abilitato per l'individuazione
	*/

	GPHEN0 = 24,	// 0x 7E20 0064
	GPHEN1 = 25,	// 0x 7E20 0068

	/*
		= I 2 registri per l'abilitazione dell'evento del segnale "basso" (da 0 a 1) =

		=================GPLEN===============
		pin	31 ...                      ... 0
		0.	 00000000000000000000000000000000	32 bit = 32 pin
		pin	        53 ...              ... 32
		1.	 xxxxxxxx000000000000000000000000	32 bit = 24 pin + 8 inutilizzati
		=====================================

		= Codice =

		0 = Il pin X non è abilitato per l'individuazione
		1 = Il pin X è abilitato per l'individuazione
	*/

	GPLEN0 = 27,	// 0x 7E20 0070
	GPLEN1 = 28,	// 0x 7E20 0074

	/*
		= Il registro di abilitazione del controllo pull-up/down =

		=================GPPUD===============
		0.	 xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx00	32 bit = 2 bit di controllo + 8 inutilizzati
		=====================================

		= Codice =

		00 = Controllo pull-up/down disabilitato
		01 = Controllo pull down abilitato
		10 = Controllo pull up abilitato
		11 = Riservato
	*/

	GPPUD0 = 37,	// 0x 7E20 0094

	/*
		= I 2 registri di clock per il controllo pull-up/down =

		Questi registri devono essere utilizzati in aggiunta al registro precedente.
		E' richiesta la seguente sequenza di eventi:

		1. Scrivere nel registro GPPUD per abilitare il controllo del segnale
		2. Aspettare 150 cicli - questo fornisce l'attesa necessaria per il controllo del segnale
		3. Scrivere sui registri GPPUDCLK0/1 per avviare il clock sull'elettrodo che tu desideri modificare
		4. Aspettare 150 cicli - questo fornisce l'attesa necessaria per il controllo del segnale
		5. Scrivere nel registro GPPUD per disabilitare il controllo del segnale
		3. Scrivere sui registri GPPUDCLK0/1 per rimuovere il clock

		===============GPPUDCLK==============
		pin	31 ...                      ... 0
		0.	 00000000000000000000000000000000	32 bit = 32 pin
		pin	        53 ...              ... 32
		1.	 xxxxxxxx000000000000000000000000	32 bit = 24 pin + 8 inutilizzati
		=====================================

		= Codice =

		0 = Nessun effetto sul pin X
		1 = Imposto il clock sul pin X
	*/

	GPPUDCLK0 = 38,	// 0x 7E20 0098
	GPPUDCLK1 = 39	// 0x 7E20 009C
};


/* INTERFACCIA DEL CONTROLLER GPIO */
class gpio {

public:

	// Pin del Raspberry Pi
	enum {

	#if RPI_CPU_REVISION == 0002 || RPI_CPU_REVISION == 0003

		PIN3	= 0,	PIN5	= 1,	PIN7	= 4,
		PIN8	= 14,	PIN10	= 15,	PIN11	= 17,
		PIN12	= 18,	PIN13	= 21,	PIN15	= 22,
		PIN16	= 23,	PIN18	= 24,	PIN19	= 10,
		PIN21	= 9,	PIN22	= 25,	PIN23	= 11,
		PIN24	= 8,	PIN26	= 7

	#else // if RPI_CPU_REVISION == 0002 || RPI_CPU_REVISION == 0004 || RPI_CPU_REVISION == 0006

		PIN3	= 2,	PIN5	= 3,	PIN7	= 4,
		PIN8	= 14,	PIN10	= 15,	PIN11	= 17,
		PIN12	= 18,	PIN13	= 27,	PIN15	= 22,
		PIN16	= 23,	PIN18	= 24,	PIN19	= 10,
		PIN21	= 9,	PIN22	= 25,	PIN23	= 11,
		PIN24	= 8,	PIN26	= 7

	#endif

	};

	// Modalità del gpio
	enum Level { LOW = 0, HIGH = 1 };
	enum PinMode { INPUT = 0, OUTPUT = 1 };
	enum PullMode { PUD_OFF = 0, PULL_DOWN = 1, PULL_UP = 2 };

	// Metodi costruttore e distruttore
	gpio();
	virtual ~gpio();

	// Imposta la modalità di un pin
	void setup( uint8_t pin, PinMode mode );
	void setup( uint8_t pin, PinMode mode, PullMode pud_mode );
	// Imposta il valore di un pin di uscita
	void write( uint8_t pin, bool value );
	// Ritorna il valore di un pin di ingresso 
	bool read( uint8_t pin );
	// Ritorna lo stato di un evento di un pin 
	bool getEvent( uint8_t pin );
	// Abilita/disabilita l'evento di "risalita" del segnale su un pin
	void setRisingEvent( uint8_t pin, bool value );
	// Abilita/disabilita l'evento di "caduta" del segnale su un pin
	void setFallingEvent( uint8_t pin, bool value );
	// Abilita/disabilita l'evento del segnale "alto" su un pin
	void setHighEvent( uint8_t pin, bool value );
	// Abilita/disabilita l'evento del segnale "basso" su un pin
	void setLowEvent( uint8_t pin, bool value );
	// Abilita/disabilita il controllo pull-up/down su tutti i pin
	void setPullUpDown( uint8_t pin, PullMode mode );

private:

	// Descrittore di file per `/dev/mem`
	int mem_fd;

	// Mapping dell'area di memoria relativa al controller gpio
	uint32_t *map;

	// Indirizzo virtuale del controller gpio
	volatile uint32_t *addr;

	// Imposta il valore di un bit su uno dei registri a 32 bit
	void setBit( uint8_t offset, uint8_t index, bool value );
	// Ritorna il valore di un bit su uno dei registri a 32 bit
	bool getBit( uint8_t offset, uint8_t index );

	// Aspetta un certo numero di cicli
	void waitCycles( size_t cycles );

	// Disegna il contenuto di un registro (funzione di debug)
	void print_register( uint8_t offset, uint8_t group_bits );
};

} // Chiudo il namespace di Rpi-hw

#endif
