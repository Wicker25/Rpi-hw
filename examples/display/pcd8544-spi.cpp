/* 
    Title --- pcd8544-spi.cpp [examples]

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


// Include Rpi-hw headers
#include <rpi-hw.hpp>
#include <rpi-hw/image/bitmap.hpp>
#include <rpi-hw/display/pcd8544-spi.hpp>

// Use some namespaces
using namespace rpihw;
using namespace rpihw::display;

int
main( int argc, char *args[] ) {

	// Create the display controller
	pcd8544_spi dev( "/dev/spidev0.0", 25, 7 );

	// Initialize the display
	dev.init();

	// Load and show the image
	image::bitmap< bool > img( "images/main_logo.png" );
	dev.drawImage( img, 0, 0 );

	dev.redraw();

	return 0;
}

