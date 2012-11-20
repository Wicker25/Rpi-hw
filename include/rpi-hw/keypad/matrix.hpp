/* 
    Title --- keypad/matrix.hpp

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


#ifndef _RPI_HW_KEYPAD_MATRIX_HPP_
#define _RPI_HW_KEYPAD_MATRIX_HPP_

#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>
#include <rpi-hw/utils.hpp>

#include <rpi-hw/bitset.hpp>

#include <rpi-hw/iface/base.hpp>
#include <rpi-hw/iface/output.hpp>
#include <rpi-hw/iface/input.hpp>

#include <rpi-hw/keypad/base.hpp>

namespace rpihw { // Begin main namespace

namespace keypad { // Begin keypads namespace

/* MATRIX KEYPAD CONTROLLER */
class matrix : public keypad::base {

public:

	// Constructor and destructor methods
	matrix( uint8_t cols, uint8_t rows, ... );
	virtual ~matrix();

protected:

	// Columns output interface
	iface::output *m_output;

	// Size of the matrix
	uint8_t m_cols, m_rows;

	// Updates the state of buttons
	virtual void update();
};

} // End of keypads namespace

} // End of main namespace

#endif
