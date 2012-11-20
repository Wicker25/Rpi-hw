/* 
    Title --- iface/output.hpp

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

/* OUTPUT INTERFACE */
class output : public iface::base {

public:

	// Constructor and destructor methods
	output( uint8_t total, ... );
	output( const std::vector< uint8_t > &pins );
	virtual ~output();

	// Sets a interface pin
	virtual void setPin( uint8_t index, uint8_t pin );

	// Writes on the interface
	virtual void write( size_t value );
	virtual void write( uint8_t pin, bool value );

protected:

	// Constructor method (only for child class)
	output();

	// Initializes the interface
	virtual void init( const std::vector< uint8_t > &pins );
};

} // End of interfaces namespace

} // End of main namespace

#endif
