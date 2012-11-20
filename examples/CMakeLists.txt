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

	add_executable( s7seg ${CMAKE_SOURCE_DIR}/s7seg.cpp )
	target_link_libraries( s7seg ${RPI_HW_LIBRARIES} )

	add_executable( m7seg0 ${CMAKE_SOURCE_DIR}/m7seg0.cpp )
	target_link_libraries( m7seg0 ${RPI_HW_LIBRARIES} )

	add_executable( m7seg1 ${CMAKE_SOURCE_DIR}/m7seg1.cpp )
	target_link_libraries( m7seg1 ${RPI_HW_LIBRARIES} )

	add_executable( lcd16x2 ${CMAKE_SOURCE_DIR}/lcd16x2.cpp )
	target_link_libraries( lcd16x2 ${RPI_HW_LIBRARIES} )

	add_executable( lcd20x4demo ${CMAKE_SOURCE_DIR}/lcd20x4demo.cpp )
	target_link_libraries( lcd20x4demo ${RPI_HW_LIBRARIES} )

	add_executable( 12keys0 ${CMAKE_SOURCE_DIR}/12keys0.cpp )
	target_link_libraries( 12keys0 ${RPI_HW_LIBRARIES} )

	add_executable( 12keys1 ${CMAKE_SOURCE_DIR}/12keys1.cpp )
	target_link_libraries( 12keys1 ${RPI_HW_LIBRARIES} )

ELSE ( RPI_HW_FOUND )

	# Log di lavoro
	MESSAGE( FATAL_ERROR "-- Could NOT find Rpi-hw!" )

ENDIF ( RPI_HW_FOUND )

