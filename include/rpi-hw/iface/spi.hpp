/* 
	Title --- spi.hpp

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


#ifndef _RPI_HW_IFACE_SPI_HPP_
#define _RPI_HW_IFACE_SPI_HPP_

#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

#include <rpi-hw/rpi.hpp>

#include <rpi-hw/types.hpp>
#include <rpi-hw/exception.hpp>
#include <rpi-hw/utils.hpp>

namespace rpihw { // Begin main namespace

namespace iface { // Begin interfaces namespace

/*!
	@class spi
	@brief Serial Peripheral Interface.
*/
class spi {

public:

	//! The SPI modes (see: https://www.kernel.org/doc/Documentation/spi/spi-summary).
	enum SpiMode {

		MODE_0	= SPI_MODE_0,	//!< Sets CPOL=0, SPI_CPHA=0.
		MODE_1	= SPI_MODE_1,	//!< Sets CPOL=0, SPI_CPHA=1.
		MODE_2	= SPI_MODE_2,	//!< Sets CPOL=1, SPI_CPHA=0.
		MODE_3	= SPI_MODE_3	//!< Sets CPOL=1, SPI_CPHA=1.
	};

	/*!
		@brief Constructor method.
		@param[in] dev_path The device path.
		@param[in] mode The SPI mode.
		@param[in] word_len The device word length.
		@param[in] speed The device max speed (hz).
	*/
	spi( const std::string &dev_path, SpiMode mode, uint8_t word_len, uint32_t speed );

	//! Destructor method.
	virtual ~spi();

	/*!
		@brief Sets the SPI mode.
		@param[in] mode The new SPI mode.
	*/
	void setMode( uint8_t mode );

	/*!
		@brief Sets the device word length.
		@param[in] word_len The bits per word.
	*/
	void setWordLen( uint8_t word_len );

	/*!
		@brief Sets the device max speed.
		@param[in] speed The new device speed.
	*/
	void setSpeed( uint32_t speed );

	//! Sends/receives a data buffer. 
	void transfer( uint8_t *data, size_t size );

private:

	//! The device path.
	std::string m_dev_path;

	//! SPI mode.
	uint8_t m_mode;

	//! Device word length.
	uint8_t m_word_len;

	//! Device max speed (hz).
	uint32_t m_speed;

	//! File descriptor of the device.
	int m_dev_fd;
};

} // End of interfaces namespace

} // End of main namespace


// Include inline methods 
#include <rpi-hw/iface/spi-inl.hpp>

#endif /* _RPI_HW_IFACE_SPI_HPP_ */
