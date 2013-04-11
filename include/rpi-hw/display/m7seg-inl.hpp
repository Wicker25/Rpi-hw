/* 
    Title --- display/m7seg-inl.hpp

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


#ifndef _RPI_HW_DISPLAY_M7SEG_INL_HPP_
#define _RPI_HW_DISPLAY_M7SEG_INL_HPP_

namespace rpihw { // Begin main namespace

namespace display { // Begin displays namespace

inline void
m7seg::setDisplays( size_t ndisplay, iface::output &enabler ) {

	// Store the number of displays and the enabler interface
	m_ndisplay = ndisplay;
	m_enabler = &enabler;
}

inline void
m7seg::setFreq( float frequency ) {

	// Store the updating frequency
	m_frequency = frequency;
}

inline float
m7seg::getFreq() const {

	// Return the updating frequency
	return m_frequency;
}

} // End of displays namespace

} // End of main namespace

#endif
