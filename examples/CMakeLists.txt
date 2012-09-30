# CMake's configuration

# Vincolo sulle versioni minori di CMake
cmake_minimum_required( VERSION 2.6 )

# Aggiungo una direttiva al compilatore
add_definitions( -Wall -ansi -pedantic -pedantic-errors )

# Imposto le dipendenze necessarie per gli esempi e gli strumenti
find_package( RpiHw )

# Controllo se è stata trovata la libreria di Serotonina
IF ( RPI_HW_FOUND )

	# Compilo tutti gli esempi
	add_executable( blink ${CMAKE_SOURCE_DIR}/blink.cpp )
	target_link_libraries( blink ${RPI_HW_LIBRARIES} )

ELSE ( RPI_HW_FOUND )

	# Log di lavoro
	MESSAGE( FATAL_ERROR "-- Could NOT find Rpi-hw!" )

ENDIF ( RPI_HW_FOUND )

