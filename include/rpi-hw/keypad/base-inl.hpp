/* 
    Title --- keypad/base-inl.hpp

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


#ifndef _RPI_HW_KEYPAD_BASE_INL_HPP_
#define _RPI_HW_KEYPAD_BASE_INL_HPP_

namespace rpihw { // Begin main namespace

namespace keypad { // Begin keypads namespace

inline void
base::addEventListener( T_EventListener listener ) {

	// Set the keypad event listener
	m_event_listener = listener;
}

inline void
base::setRefreshRate( float frequency ) {

	// Set the frequency with which buttons are read
	m_frequency = frequency;
}

inline float
base::getRefreshRate() const {

	// Returns the frequency with which buttons are read
	return m_frequency;
}

inline const std::vector< bool > &
base::state() const {

	// Return the list of button states
	return m_keystate;
}

inline size_t
base::numOfKeys() const {

	// Return the number of keys
	return m_nkeys;
}

} // End of keypads namespace

} // End of main namespace

#endif /* _RPI_HW_KEYPAD_BASE_INL_HPP_ */
