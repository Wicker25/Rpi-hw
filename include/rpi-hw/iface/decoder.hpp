/* 
    Title --- iface/decoder.hpp

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


#ifndef _RPI_HW_IFACE_DECODER_HPP_
#define _RPI_HW_IFACE_DECODER_HPP_

#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>
#include <rpi-hw/math.hpp>
#include <rpi-hw/utils.hpp>

#include <rpi-hw/iface/base.hpp>
#include <rpi-hw/iface/output.hpp>

namespace rpihw { // Begin main namespace

namespace iface { // Begin interfaces namespace

/* DECODER OUTPUT INTERFACE */
class decoder : public iface::output {

public:

	// Constructor and destructor methods
	decoder( uint8_t total, ... );
	virtual ~decoder();

	// Writes on the interface
	virtual void write( size_t value );
};

} // End of interfaces namespace

} // End of main namespace

#endif
