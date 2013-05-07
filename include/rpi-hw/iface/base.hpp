/* 
    Title --- iface/base.hpp

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


#ifndef _RPI_HW_IFACE_BASE_HPP_
#define _RPI_HW_IFACE_BASE_HPP_

#include <memory>
#include <initializer_list>
#include <vector>

#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>
#include <rpi-hw/utils.hpp>

#include <rpi-hw/gpio.hpp>

namespace rpihw { // Begin main namespace

/*!
	@namespace rpihw::iface
	@brief Namespace of the interfaces.
*/

namespace iface { // Begin interfaces namespace

/*!
	@class base
	@brief Generic interface.
*/
class base {

public:

	/*!
		@brief Constructor method.
		@param[in] pins Sequence of `uint8_t` containing the GPIO pins.
	*/
	base( std::initializer_list< uint8_t > pins );

	/*!
		@brief Constructor method.
		@param[in] pins Vector containing the GPIO pins.
	*/
	base( const std::vector< uint8_t > &pins );

	//! Destructor method.
	virtual ~base();

	/*!
		@brief Sets an interface pin.
		@param[in] index The index position of the interface pin.
		@param[in] pin The new GPIO pin.
	*/
	virtual void setPin( uint8_t index, uint8_t pin );

	/*!
		@brief Returns an interface pin.
		@param[in] index The index position of the interface pin.
		@return The GPIO pin.
	*/
	virtual uint8_t getPin( uint8_t index ) const;

	//! Returns the number of the pins.
	virtual uint8_t numOfPins() const;

protected:

	//! GPIO controller interface.
	std::unique_ptr< gpio > m_gpio;

	//! Vector containing interface pins.
	std::vector< uint8_t > m_pins;
};

} // End of interfaces namespace

} // End of main namespace


// Include inline methods 
#include <rpi-hw/iface/base-inl.hpp>

#endif /* _RPI_HW_IFACE_BASE_HPP_ */
