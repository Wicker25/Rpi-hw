/* 
    Title --- display/pcd8544-skeleton-inl.hpp

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


#ifndef _RPI_HW_DISPLAY_PCD8544_SKELETON_INL_HPP_
#define _RPI_HW_DISPLAY_PCD8544_SKELETON_INL_HPP_

namespace rpihw { // Begin main namespace

namespace display { // Begin displays namespace

inline void
pcd8544_skeleton::setColor( bool color ) {

	// Set the foreground color
	setPenColor( { color } );
}

inline bool
pcd8544_skeleton::getColor() const {

	// Set the foreground color
	return getPenColor()[0];
}

inline void
pcd8544_skeleton::setPixel( int8_t x, int8_t y, bool color ) {

	// Set the pixel color
	std::vector< bool > c = { color };
	drawPixel( x, y, std::begin( c ) );
}

} // End of displays namespace

} // End of main namespace

#endif /* _RPI_HW_DISPLAY_PCD8544_SKELETON_INL_HPP_ */
