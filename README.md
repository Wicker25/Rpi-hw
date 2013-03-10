Rpi-hw v0.2.6
=============

### Description

[Rpi-hw](http://www.hackyourmind.org/blog/projects/rpi-hw/) is a free C++ library 
designed to manage the Raspberry Pi's General Purpose Input/Output (GPIO) connector.
The library is released under terms of the [GNU LGPL v3](http://en.wikipedia.org/wiki/GNU_Lesser_General_Public_License).

The source of the latest version of Rpi-hw is available on [github.com](https://github.com/Wicker25/Rpi-hw) at:

- [https://github.com/Wicker25/Rpi-hw](https://github.com/Wicker25/Rpi-hw)

### Main functions

The following are some functions of the library:

* Low-level management of the GPIOs
* Generic input/output by interfaces
* Keypad support (matrix keypad)
* Display support (7-segments, HD44780 lcd)

### Compiling and install the library

First of all, you need to clone the Rpi-hw repository:

    $ git clone https://github.com/Wicker25/Rpi-hw

Then, compile and install the library with:

    $ cd Rpi-hw
    $ cmake ./ -DCMAKE_INSTALL_PREFIX=<PATH>
    $ make
    # make install

Also, if you want a local copy of the documentation, 
you can generate it using [doxygen](https://en.wikipedia.org/wiki/Doxygen):

    $ make doc

### Using the library

To use the library, you must include the main Rpi-hw‘s header file into your program:

    // Include the main header file
    #include <rpi-hw.hpp>

Then, you link the program's file with the library object file, adding a command line argument to the compiler:

    $ g++ `pkg-config --libs --cflags rpi-hw` <SOURCE> -o <BIN>

Otherwise, you can use [CMake](http://en.wikipedia.org/wiki/CMake) with the module `FindRpiHw.cmake` 
provided by the library. See the following example:

    # CMake's configuration

    # Set the minimum required version of cmake for this project
    cmake_minimum_required( VERSION 2.6 )

    # Find Rpi-hw library on the operating system
    find_package( RpiHw )

    # Check if the library was found
    IF ( RPI_HW_FOUND )

        # Compile the project
        add_executable( <BIN> ${CMAKE_SOURCE_DIR}/<SOURCE> )

        # Link the library
        target_link_libraries( <BIN> ${RPI_HW_LIBRARIES} )

    ENDIF ( RPI_HW_FOUND )

### Documentation and examples

If you are looking for examples, you can find some into the directory of the source code, 
else you can see some post about the library at this [link](http://www.hackyourmind.org/blog/category/rpi-hw/).
See also the reference manual, available at:

* [http://www.rpihw.hackyourmind.org/](http://www.rpihw.hackyourmind.org/)

### Links

* [http://www.hackyourmind.org/blog/](http://www.hackyourmind.org/blog/)

