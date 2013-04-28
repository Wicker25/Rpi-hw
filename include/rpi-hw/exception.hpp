/* 
    Title --- exception.hpp

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


#ifndef _RPI_HW_EXCEPTION_HPP_
#define _RPI_HW_EXCEPTION_HPP_

#include <stdexcept>

#include <rpi-hw/utils.hpp>
#include <rpi-hw/utils-inl.hpp>

#define exception( x ) exception_class( __FILE__, __LINE__, x )

namespace rpihw { // Begin main namespace

/*!
	@class exception_class
	@brief Runtime exception class.
*/
class exception_class : public std::runtime_error {

public:

	//! Constructor method.
	exception_class( const char *file, size_t line, const std::string &message ) :
		std::runtime_error( utils::format( "%s:%lu: \n\t\t", file, line ) + message ) { }
};

} // End of main namespace

#endif /* _RPI_HW_EXCEPTION_HPP_ */
