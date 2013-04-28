/* 
    Title --- iface/decoder-out-inl.hpp

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


#ifndef _RPI_HW_IFACE_DECODER_IN_INL_HPP_
#define _RPI_HW_IFACE_DECODER_IN_INL_HPP_

namespace rpihw { // Begin main namespace

namespace iface { // Begin interfaces namespace

inline void
decoderOut::write( size_t value ) {

	// Write on the interface
	output::write( math::fast_pow2( value ) );
}

} // End of interfaces namespace

} // End of main namespace

#endif /* _RPI_HW_IFACE_DECODER_IN_INL_HPP_ */
