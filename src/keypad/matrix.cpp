/* 
    Title --- keypad/matrix.cpp

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


#ifndef _RPI_HW_KEYPAD_MATRIX_CPP_
#define _RPI_HW_KEYPAD_MATRIX_CPP_

#include <rpi-hw/keypad/matrix.hpp>

namespace rpihw { // Begin main namespace

namespace keypad { // Begin keypads namespace

matrix::matrix( std::initializer_list< uint8_t > cols, std::initializer_list< uint8_t > rows )

	: keypad::base( cols.size() * rows.size(), rows )
	, m_output( new iface::output( cols ) ) {

}

matrix::~matrix() {

}

void
matrix::update() {

	// Get the size of the keypad
	uint8_t cols = m_output->numOfPins(),
			rows = m_input->numOfPins();

	// Working structures
	size_t index, state, rows_value;

	// Iterators
	uint8_t i, j;

	// Updating loop
	while ( 1 ) {

		// Update state of buttons
		for ( j = 0; j < cols; ++j ) {

			// Activate the j-th column
			m_output->write( 1 << j );
			rows_value = m_input->read();

			for ( i = 0; i < rows; ++i ) {

				// Look for connection with i-th row
				state = rows_value & ( 1 << i );
				index = (size_t) j + (size_t) i * (size_t) cols;

				// Update the button registers
				m_mutex->lock();

				m_pressed[ index ]	= ( !m_keystate[ index ] && state );
				m_released[ index ]	= ( m_keystate[ index ] && !state );
				m_keystate[ index ]	= state;

				m_mutex->unlock();
			}
		}

		// Wait some time (100 ms)
		time::msleep( 100 );
	}
}

} // End of keypads namespace

} // End of main namespace

#endif /* _RPI_HW_KEYPAD_MATRIX_CPP_ */
