/* 
    Title --- driver/spi.cpp

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


#ifndef _RPI_HW_DRIVER_SPI_CPP_
#define _RPI_HW_DRIVER_SPI_CPP_

#include <rpi-hw/driver/spi.hpp>

namespace rpihw { // Begin main namespace

namespace driver { // Begin drivers namespace

spi::spi( const std::string &dev_path, Modes mode, uint8_t word_len, uint32_t speed )

	: m_dev_path	( dev_path )
	, m_mode		( (uint8_t) mode )
	, m_word_len	( word_len )
	, m_speed		( speed ) {


	// Open device file
	m_dev_fd = open( m_dev_path.c_str(), O_RDWR );

	if ( m_dev_fd < 0 )
		throw exception( "(Fatal) `spi`: can't open SPI device" );


	// Set the SPI mode
	setMode( m_mode );

	// Set the device word length
	setWordLen( m_word_len );

	// Set the device max speed
	setSpeed( m_speed );
}

spi::~spi() {

	// Close device file
	close( m_dev_fd );
}

void
spi::setMode( uint8_t mode ) {

	// Set the SPI mode
	m_mode = mode;

	if ( ioctl( m_dev_fd, SPI_IOC_WR_MODE, &m_mode ) < 0 )
		throw exception( "(Fatal) `spi`: can't set SPI mode (WR)" );

	if ( ioctl( m_dev_fd, SPI_IOC_RD_MODE, &m_mode ) < 0 )
		throw exception( "(Fatal) `spi`: can't set SPI mode (RD)" );
}

void
spi::setWordLen( uint8_t word_len ) {

	// Set the device word length
	m_word_len = word_len;

	if ( ioctl( m_dev_fd, SPI_IOC_WR_BITS_PER_WORD, &m_word_len ) < 0 )
		throw exception( "(Fatal) `spi`: can't set SPI bit per words (WR)" );

	if ( ioctl( m_dev_fd, SPI_IOC_RD_BITS_PER_WORD, &m_word_len ) < 0 )
		throw exception( "(Fatal) `spi`: can't set SPI bit per words (RD)" );
}

void
spi::setSpeed( uint32_t speed ) {

	// Set the device max speed
	m_speed = speed;

	// Set SPI speed
	if ( ioctl( m_dev_fd, SPI_IOC_WR_MAX_SPEED_HZ, &m_speed ) < 0 )
		throw exception( "(Fatal) `spi`: can't set SPI speed (WR)" );

	if ( ioctl( m_dev_fd, SPI_IOC_RD_MAX_SPEED_HZ, &m_speed ) < 0 )
		throw exception( "(Fatal) `spi`: can't set SPI speed (RD)" );
}

void
spi::transfer( uint8_t *data, size_t size ) {

	// Build the request structure
	spi_ioc_transfer spi_data;

	spi_data.tx_buf			= (size_t) data;
	spi_data.rx_buf			= (size_t) data;
	spi_data.len			= size;
	spi_data.delay_usecs	= 0;
	spi_data.speed_hz		= m_speed;
	spi_data.bits_per_word	= m_word_len;
	spi_data.cs_change		= 0;

	// Send/receive the data buffer
	if ( ioctl( m_dev_fd, SPI_IOC_MESSAGE(1), &spi_data ) < 0 )
		throw exception( "(Fatal) `spi`: transmission error" );
}

} // End of drivers namespace

} // End of main namespace

#endif /* _RPI_HW_DRIVER_SPI_CPP_ */
