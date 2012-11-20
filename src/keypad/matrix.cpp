/* 
    Title --- keypad/matrix.cpp

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


#ifndef _RPI_HW_KEYPAD_MATRIX_CPP_
#define _RPI_HW_KEYPAD_MATRIX_CPP_

#include <rpi-hw/keypad/matrix.hpp>

#include <rpi-hw/utils.hpp>
#include <rpi-hw/utils-inl.hpp>

#include <rpi-hw/bitset.hpp>
#include <rpi-hw/bitset-inl.hpp>

#include <rpi-hw/gpio.hpp>
#include <rpi-hw/gpio-inl.hpp>

#include <rpi-hw/iface/base.hpp>
#include <rpi-hw/iface/base-inl.hpp>

#include <rpi-hw/iface/output.hpp>
#include <rpi-hw/iface/output-inl.hpp>

#include <rpi-hw/iface/input.hpp>
#include <rpi-hw/iface/input-inl.hpp>

#include <rpi-hw/keypad/base.hpp>
#include <rpi-hw/keypad/base-inl.hpp>

#include <rpi-hw/keypad/matrix-inl.hpp>

namespace rpihw { // Begin main namespace

namespace keypad { // Begin keypads namespace

matrix::matrix( uint8_t cols, uint8_t rows, ... ) : m_cols( cols ), m_rows( rows ) {

	// Initialize variable argument list
	va_list args;
	va_start( args, rows );

	// Create the columns output interface
	m_output = new iface::output( utils::varg< uint8_t, int >( args, cols ) );

	// Initialize the instance
	init( (size_t) cols * (size_t) rows, utils::varg< uint8_t, int >( args, rows, cols ) );

	// Clean variable argument list
	va_end( args );
}

matrix::~matrix() {

	// Destroy the output interface
	delete m_output;
}

void
matrix::update() {

	// Working structures
	size_t index, state, rows_value;

	// Iterators
	uint8_t i, j;

	// Updating loop
	while ( 1 ) {

		// Update state of buttons
		for ( j = 0; j < m_cols; j++ ) {

			// Activate the j-th column
			m_output->write( 1 << j );
			rows_value = m_input->read();

			for ( i = 0; i < m_rows; i++ ) {

				// Look for connection with i-th row
				state = rows_value & ( 1 << i );
				index = (size_t) j + (size_t) i * (size_t) m_cols;

				// Update the button registers
				m_mutex->lock();

				m_pressed->set( index, !m_keystate->get( index ) && state );
				m_released->set( index, m_keystate->get( index ) && !state );
				m_keystate->set( index, state );

				m_mutex->unlock();
			}
		}

		// Wait some time (100 ms)
		utils::msleep( 100 );
	}
}

} // End of keypads namespace

} // End of main namespace

#endif
