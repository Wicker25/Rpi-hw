/* 
    Title --- iface/shift-base.hpp

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


#ifndef _RPI_HW_IFACE_SHIFT_BASE_HPP_
#define _RPI_HW_IFACE_SHIFT_BASE_HPP_

#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>
#include <rpi-hw/math.hpp>
#include <rpi-hw/utils.hpp>
#include <rpi-hw/time.hpp>

#include <rpi-hw/iface/base.hpp>

namespace rpihw { // Begin main namespace

namespace iface { // Begin interfaces namespace

/*!
	@class shiftBase
	@brief Shift base interface.
*/
class shiftBase : public iface::base {

public:

	//! Shift interface pins.
	enum ShiftPins {

		DATA	= 0,	//!< The data pin.
		CLOCK	= 1		//!< The clock pin.
	};

	//! Bit orders.
	enum BitOrder {

		MSBFIRST	= 0,	//!< Most significant bit first.
		LSBFIRST	= 1		//!< Least significant bit first.
	};

	/*!
		@brief Constructor method.
		@param[in] data_pin The data pin.
		@param[in] clock_pin The clock pin.
		@param[in] order The bit order.
		@param[in] delay The delay time of the clock.
	*/
	shiftBase( uint8_t data_pin, uint8_t clock_pin, BitOrder order, size_t delay = 0 );

	//! Destructor method.
	virtual ~shiftBase();

	//! Toggles the clock.
	virtual void strobe();

protected:

	//! The order to shift out the bits.
	BitOrder m_order;

	//! The delay time of the clock.
	size_t m_delay;
};

} // End of interfaces namespace

} // End of main namespace


// Include inline methods 
#include <rpi-hw/iface/shift-base-inl.hpp>

#endif /* _RPI_HW_IFACE_SHIFT_BASE_HPP_ */
