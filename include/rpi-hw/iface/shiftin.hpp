/* 
    Title --- iface/shiftin.hpp

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


#ifndef _RPI_HW_IFACE_SHIFTIN_HPP_
#define _RPI_HW_IFACE_SHIFTIN_HPP_

#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>
#include <rpi-hw/math.hpp>
#include <rpi-hw/utils.hpp>

#include <rpi-hw/iface/base.hpp>
#include <rpi-hw/iface/shift-base.hpp>

namespace rpihw { // Begin main namespace

namespace iface { // Begin interfaces namespace

/*!
	@class shiftIn
	@brief Shift-in interface.
*/
class shiftIn : public shiftBase {

public:

	/*!
		@brief Constructor method.
		@param[in] data_pin The data pin.
		@param[in] clock_pin The clock pin.
		@param[in] order The bit order.
		@param[in] delay The delay time of the clock.
	*/
	shiftIn( uint8_t data_pin, uint8_t clock_pin, BitOrder order, size_t delay = 0 );

	//! Destructor method.
	virtual ~shiftIn();

	/*!
		@brief Sets an shiftIn pin.
		@param[in] index The index position of the shiftIn pin.
		@param[in] pin The new GPIO pin.
	*/
	virtual void setPin( uint8_t index, uint8_t pin );

	/*!
		@brief Reads from the interface.
		@return The data read from the interface.
	*/
	virtual uint8_t read();
};

} // End of interfaces namespace

} // End of main namespace

#endif
