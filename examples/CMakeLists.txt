# Rpi-hw examples

# Set the minimum required version of CMake
cmake_minimum_required( VERSION 2.6 )

# Set the compiler flags
add_definitions( -Wall -ansi -pedantic -pedantic-errors )

# Find the Rpi-hw library
find_package( RpiHw )

IF ( RPI_HW_FOUND )

	# Build all examples
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

	MESSAGE( FATAL_ERROR "-- Could NOT find Rpi-hw!" )

ENDIF ( RPI_HW_FOUND )

