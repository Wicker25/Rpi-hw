/* 
    Title --- display/pcd8544-spi.hpp

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


#ifndef _RPI_HW_DISPLAY_PCD8544_SPI_HPP_
#define _RPI_HW_DISPLAY_PCD8544_SPI_HPP_

#include <memory>

#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>
#include <rpi-hw/math.hpp>

#include <rpi-hw/iface/spi.hpp>

#include <rpi-hw/display/pcd8544-skeleton.hpp>

namespace rpihw { // Begin main namespace

namespace display { // Begin displays namespace

/*!
	@class pcd8544_spi
	@brief Philips PCD8544 LCD controller (via SPI).

	@example display/pcd8544-spi.cpp
*/
class pcd8544_spi : public pcd8544_skeleton {

public:

	/*!
		@brief Constructor method.
		@param[in] dev_path The device path.
		@param[in] dc The GPIO pin connected to the dorc pin.
		@param[in] rst The GPIO pin connected to the rst pin.
	*/
	pcd8544_spi( const std::string &dev_path, uint8_t dc, uint8_t rst );

	//! Destructor method.
	virtual ~pcd8544_spi();

	/*!
		@brief Sends a command to the display.
		@param[in] data The command.
	*/
	virtual void cmd( uint8_t data );

	/*!
		@brief Sends a data to the display.
		@param[in] data The 8-bit data to be sended.
	*/
	virtual void sendData( uint8_t data );

protected:

	//! SPI interface to the data pins.
	std::unique_ptr< iface::spi > m_spi;
};

} // End of displays namespace

} // End of main namespace


// Include inline methods 
#include <rpi-hw/display/pcd8544-spi-inl.hpp>

#endif /* _RPI_HW_DISPLAY_PCD8544_SPI_HPP_ */
