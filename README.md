Rpi-hw v0.7.1
=============

[Rpi-hw](http://hackyourmind.org/projects/rpi-hw) (short for "Raspberry Pi Hardware") is a free C++ library 
designed to manage the Raspberry Pi's GPIO connector and its other buses.
It allows you to connect several devices to the board (including displays, keypads, stepper motors, and sensors) as you would with Arduino's libraries.

![Ultrasonic Distance Sensor](https://raw.github.com/Wicker25/Rpi-hw/master/extras/ultrasonic_sensor.jpg) .
![PCD8544 LCD](https://raw.github.com/Wicker25/Rpi-hw/master/extras/pcd8544.png)

### Features

* Low-level access to the GPIO Connector and SPI, I2C, UART buses
* High-level input/output interfaces
* Support for I/O expander ICs
* Support for many devices, including displays, keypads, stepper motors, and sensors (see "List of supported devices" section)
* Unicode support (built-in)
* Support for standard fonts (using FreeType) (optional)
* Support for multiple image formats (using Magick++ API) (optional)
* Drawing functions

### List of supported devices

* 8-bit I/O expander with I2C/SPI (MCP23008, MCP23S08)
* 16-bit I/O expander with I2C/SPI (MCP23017, MCP23S17)
* Character LCDs (Hitachi HD44780)
* Graphical LCDs (Philips PCD8544)
* Single and multiple 7-segments diplays
* Matrix keypads
* Ultrasonic distance sensor (HC-SR04)
* Stepper motors

### To-do list

* Support for UART interface

### Code examples

Accessing to the GPIO connector:

```cpp
// Get the GPIO controller
gpio &io = gpio::get();

// Set the mode of GPIO #11
io.setup( 25, OUTPUT );

// Write on GPIO #11
io.write( 25, HIGH );
```
Reading from 16-keys keypad:

```cpp
// Define the keymap
std::vector< uint8_t > keymap = {

	'1', '2', '3', 'A',
	'4', '5', '6', 'B',
	'7', '8', '9', 'C',
	'*', '0', '#', 'D'
};

// Matrix keypad controller
keypad::matrix dev( { 14, 15, 18, 23 }, { 24, 25, 8, 7 }, keymap );

// Main loop
for ( ;; ) {

    // Check the button state
    if ( dev.keyPressed('2') || dev.keyPressed('3') )
        std::cout << "You have pressed keys '2' or '3'!\n";

	// Wait some time
	time::msleep( 100 );
}
```

Writing texts on a Hitachi HD44780-based LCD:

```cpp
// Display controller
display::hd44780 dev( 14, 18, 4, 17, 21, 22 );

// Initialize the 16x2 display
dev.init( 16, 2 );

// Move the cursor position
dev.move( 2, 0 );

// Write a string at cursor position
dev.write( "Hello World!" );
```

### Documentation

Detailed documentation of Rpi-hw's features and usage can be found on the [official wiki](https://github.com/Wicker25/Rpi-hw/wiki).

* [Download and install](https://github.com/Wicker25/Rpi-hw/wiki/Download%20and%20install)
* [Getting started](https://github.com/Wicker25/Rpi-hw/wiki/Getting%20started)
* [Reference manual](http://hackyourmind.org/rpi-hw/)

Also you can find [some articles](http://hackyourmind.org/tag/rpi-hw) about the library on <http://hackyourmind.org/>.

### License

The library is released under terms of the [GNU LGPL v3](http://en.wikipedia.org/wiki/GNU_Lesser_General_Public_License).

```
Rpi-hw is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation version 3 of the License.

Rpi-hw is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.
```

See COPYING file for more details.

### Bug tracker

Have a bug? Please create an issue on GitHub at <https://github.com/Wicker25/Rpi-hw/issues>.

