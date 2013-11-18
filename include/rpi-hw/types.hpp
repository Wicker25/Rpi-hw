/* 
    Title --- types.hpp

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


#ifndef _RPI_HW_TYPES_HPP_
#define _RPI_HW_TYPES_HPP_

#include <cstdint>
#include <vector>

namespace rpihw { // Begin main namespace

//@{
//! The basic types.
using std::int8_t;
using std::int16_t;
using std::int32_t;
using std::int64_t;

using std::uint8_t;
using std::uint16_t;
using std::uint32_t;
using std::uint64_t;
//@}

//! Color iterator.
template < typename T >
using color_iterator = typename std::vector< T >::const_iterator;

} // End of main namespace

#endif /* _RPI_HW_TYPES_HPP_ */
