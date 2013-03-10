/* 
    Title --- 12keys0.cpp [examples]

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


#include <iostream>
#include <ctime>

#include <rpi-hw.hpp>

#include <rpi-hw/utils.hpp>
#include <rpi-hw/utils-inl.hpp>

#include <rpi-hw/keypad/base.hpp>
#include <rpi-hw/keypad/base-inl.hpp>

#include <rpi-hw/keypad/matrix.hpp>
#include <rpi-hw/keypad/matrix-inl.hpp>

// Use the Rpi-hw namespace
using namespace rpihw;

/*
      (21, 10, 4)     colums = 3
          |||
   -----------------
   | (1)  (2)  (3) |
   |               |
   | (4)  (5)  (6) |
   |               |
   | (7)  (8)  (9) |
   |               |
   | (*)  (0)  (#) |
   -----------------
          ||||
    (22, 14, 15, 17)  rows = 4

*/

int
main( int argc, char *args[] ) {

   // Matrix keypad controller
   keypad::matrix disp( 3, 4, 21, 10, 4, 22, 14, 15, 17 );

   // Main loop
   for ( ;; ) {

      // Check some keys state
      if ( disp.pressed(0) )
         std::cout << "You have pressed button 0!\n";

      if ( disp.released(2) )
         std::cout << "You have released button 2!\n";

      if ( disp.pressed(1) && disp.pressed(4) )
         std::cout << "You have pressed buttons 1 and 4!\n";

      // Wait some time
      utils::msleep( 100 );
   }

   return 0;
}

