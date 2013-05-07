/* 
    Title --- iface/input.hpp

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


#ifndef _RPI_HW_IFACE_INPUT_HPP_
#define _RPI_HW_IFACE_INPUT_HPP_

#include <initializer_list>
#include <vector>

#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>
#include <rpi-hw/math.hpp>
#include <rpi-hw/utils.hpp>

#include <rpi-hw/iface/base.hpp>

namespace rpihw { // Begin main namespace

namespace iface { // Begin interfaces namespace

/*!
	@class input
	@brief Input interface.
*/
class input : public iface::base {

public:

	/*!
		@brief Constructor method.
		@param[in] pins Sequence of `uint8_t` containing the GPIO pins.
	*/
	input( std::initializer_list< uint8_t > pins );

	/*!
		@brief Constructor method.
		@param[in] pins Vector containing the GPIO pins.
	*/
	input( const std::vector< uint8_t > &pins );

	//! Destructor method.
	virtual ~input();

	/*!
		@brief Sets an input pin.
		@param[in] index The index position of the input pin.
		@param[in] pin The new GPIO pin.
	*/
	virtual void setPin( uint8_t index, uint8_t pin );

	/*!
		@brief Reads from the interface.
		@return The data read from the interface.
	*/
	virtual size_t read() const;

	/*!
		@brief Reads from the interface.
		@param[in] index The index position of the interface pin.
		@return The data read from the interface.
	*/
	virtual bool read( uint8_t index ) const;
};

} // End of interfaces namespace

} // End of main namespace


// Include inline methods 
#include <rpi-hw/iface/input-inl.hpp>

#endif /* _RPI_HW_IFACE_INPUT_HPP_ */
