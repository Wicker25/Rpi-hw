/* 
    Title --- iface/output.hpp

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


#ifndef _RPI_HW_IFACE_OUTPUT_HPP_
#define _RPI_HW_IFACE_OUTPUT_HPP_

#include <vector>

#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>
#include <rpi-hw/math.hpp>
#include <rpi-hw/utils.hpp>

#include <rpi-hw/iface/base.hpp>

namespace rpihw { // Begin main namespace

namespace iface { // Begin interfaces namespace

/*!
	@class output
	@brief Output interface.
*/
class output : public iface::base {

public:

	/*!
		@brief Constructor method.
		@param[in] total Number of the output pins.
		@param[in] ... Sequence of `uint8_t` containing the GPIO pins.
	*/
	output( uint8_t total, ... );

	/*!
		@brief Constructor method.
		@param[in] pins Vector containing the GPIO pins.
	*/
	output( const std::vector< uint8_t > &pins );

	//! Destructor method.
	virtual ~output();

	/*!
		@brief Sets an output pin.
		@param[in] index The index position of the output pin.
		@param[in] pin The new GPIO pin.
	*/
	virtual void setPin( uint8_t index, uint8_t pin );

	/*!
		@brief Writes a data on the interface.
		@param[in] data The data to be written.
	*/
	virtual void write( size_t data );

	/*!
		@brief Writes a data on the interface pin.
		@param[in] index The index position of the interface pin.
		@param[in] data The data to be written.
	*/
	virtual void write( uint8_t index, bool data );

protected:

	//! Constructor method (only for child class).
	output();

	/*!
		@brief Initializes the interface.
		@param[in] pins Vector containing the GPIO pins.
	*/
	virtual void init( const std::vector< uint8_t > &pins );
};

} // End of interfaces namespace

} // End of main namespace


// Include inline methods 
#include <rpi-hw/iface/output-inl.hpp>

#endif /* _RPI_HW_IFACE_OUTPUT_HPP_ */
