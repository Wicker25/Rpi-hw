# Project name
project( RpiHw )

# Set the minimum required version of CMake
cmake_minimum_required( VERSION 2.6 )

# Set the version of the library
set( RPI_HW_VERSION "0.2.6" )
set( RPI_HW_VERSION_MAJOR 0 )
set( RPI_HW_VERSION_MINOR 2 )
set( RPI_HW_VERSION_PATCH 6 )


# Find the dependencies
find_package( Threads REQUIRED )
find_package( Freetype REQUIRED )

# Set the compiler flags
add_definitions( -Wall -ansi -pedantic -pedantic-errors -Wno-psabi )

# Set the path of the header files
include_directories(

	${CMAKE_SOURCE_DIR}/include
	${CMAKE_BINARY_DIR}/include

	${FREETYPE_INCLUDE_DIRS}
)


# Check if RPi's Revision has been specified by user
IF ( RPI_REVISION )

	MESSAGE( "-- Using Raspberry Pi Revision Number: ${RPI_REVISION}" )

ELSE ( RPI_REVISION )

	# Find the Raspberry Pi Revision number
	# grep -Po '^Revision\s*:\s*\K[[:xdigit:]]{7}' /proc/cpuinfo
	execute_process( COMMAND grep -Po "^Revision\\s*:\\s*\\K[[:xdigit:]]+" /proc/cpuinfo
					 OUTPUT_VARIABLE RPI_REVISION )

	# If I have not found the Revision number, use the last version
	IF ( RPI_REVISION )

		MESSAGE( "-- Detecting Raspberry Pi Revision Number: ${RPI_REVISION}" )

	ELSE ( RPI_REVISION )

		set( RPI_REVISION "0006" )

		MESSAGE( WARNING "-- Could NOT find Raspberry Pi revision!" )

	ENDIF ( RPI_REVISION )

	set( RPI_REVISION "0x${RPI_REVISION}" )

ENDIF ( RPI_REVISION )


# Set the files to be modified
configure_file(

	"${CMAKE_SOURCE_DIR}/include/rpi-hw/version.hpp.in"
	"${CMAKE_BINARY_DIR}/include/rpi-hw/version.hpp"
	IMMEDIATE @ONLY
)

configure_file(

	"${CMAKE_SOURCE_DIR}/include/rpi-hw/rpi.hpp.in"
	"${CMAKE_BINARY_DIR}/include/rpi-hw/rpi.hpp"
	IMMEDIATE @ONLY
)

configure_file(

	"${CMAKE_SOURCE_DIR}/cmake/FindRpiHw.cmake.in"
	"${CMAKE_BINARY_DIR}/cmake/FindRpiHw.cmake"
	IMMEDIATE @ONLY
)

configure_file(

	"${CMAKE_SOURCE_DIR}/pkgconfig/rpi-hw.pc.in"
	"${CMAKE_BINARY_DIR}/pkgconfig/rpi-hw.pc"
	IMMEDIATE @ONLY
)

configure_file(

	"${CMAKE_SOURCE_DIR}/doxygen/doxy.conf.in"
	"${CMAKE_BINARY_DIR}/doxygen/doxy.conf"
	IMMEDIATE @ONLY
)

configure_file(

	"${CMAKE_SOURCE_DIR}/cmake_uninstall.cmake.in"
	"${CMAKE_BINARY_DIR}/cmake_uninstall.cmake"
	IMMEDIATE @ONLY
)

# Set some paths
set( LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib )
set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin )

set( RPI_HW_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/src )
set( RPI_HW_BINARY_DIR ${CMAKE_BINARY_DIR}/bin ${CMAKE_BINARY_DIR}/bin )


# Build the library
add_library( rpihw SHARED

	${RPI_HW_SOURCE_DIR}/utils.cpp
	${RPI_HW_SOURCE_DIR}/time.cpp
	${RPI_HW_SOURCE_DIR}/bitset.cpp
	${RPI_HW_SOURCE_DIR}/bitmap.cpp
	${RPI_HW_SOURCE_DIR}/gpio.cpp

	${RPI_HW_SOURCE_DIR}/iface/base.cpp
	${RPI_HW_SOURCE_DIR}/iface/output.cpp
	${RPI_HW_SOURCE_DIR}/iface/input.cpp
	${RPI_HW_SOURCE_DIR}/iface/shift-base.cpp
	${RPI_HW_SOURCE_DIR}/iface/shiftout.cpp
	${RPI_HW_SOURCE_DIR}/iface/shiftin.cpp
	${RPI_HW_SOURCE_DIR}/iface/encoder.cpp
	${RPI_HW_SOURCE_DIR}/iface/decoder.cpp

	${RPI_HW_SOURCE_DIR}/font/base.cpp
	${RPI_HW_SOURCE_DIR}/font/freetype.cpp

	${RPI_HW_SOURCE_DIR}/keypad/base.cpp
	${RPI_HW_SOURCE_DIR}/keypad/matrix.cpp

	${RPI_HW_SOURCE_DIR}/display/s7seg.cpp
	${RPI_HW_SOURCE_DIR}/display/m7seg.cpp
	${RPI_HW_SOURCE_DIR}/display/hd44780.cpp
	${RPI_HW_SOURCE_DIR}/display/pcd8544.cpp

	${RPI_HW_SOURCE_DIR}/motor/stepper.cpp
)

target_link_libraries( rpihw ${CMAKE_THREAD_LIBS_INIT} )
target_link_libraries( rpihw ${FREETYPE_LIBRARIES} )
target_link_libraries( rpihw rt )

# Build the executables
add_executable( rpi-gpio ${RPI_HW_SOURCE_DIR}/rpi-gpio.cpp )
target_link_libraries( rpi-gpio rpihw )

add_executable( test ${RPI_HW_SOURCE_DIR}/test.cpp )
target_link_libraries( test rpihw )


# If Doxygen found, define the function `make doc`
find_package( Doxygen )

if ( DOXYGEN_FOUND )

	add_custom_target( doc COMMAND doxygen doxygen/doxy.conf )
	add_custom_target( doc-clean COMMAND rm -R "${CMAKE_SOURCE_DIR}/doc" )

endif ( DOXYGEN_FOUND )


# Define the library installer
install_targets( /lib rpihw )

install( FILES ${CMAKE_SOURCE_DIR}/include/rpi-hw.hpp
		 DESTINATION ${CMAKE_INSTALL_PREFIX}/include )

install( DIRECTORY ${CMAKE_SOURCE_DIR}/include/rpi-hw
		 DESTINATION ${CMAKE_INSTALL_PREFIX}/include
		 FILES_MATCHING
		 PATTERN "*"
		 PATTERN "*.in" EXCLUDE )

# Pkg-config installer
install( FILES ${CMAKE_SOURCE_DIR}/pkgconfig/rpi-hw.pc
		 DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig )

# CMake installer
install( FILES ${CMAKE_SOURCE_DIR}/cmake/FindRpiHw.cmake
		 DESTINATION ${CMAKE_ROOT}/Modules/ )

# Tools installer
install( FILES ${CMAKE_SOURCE_DIR}/bin/rpi-gpio
		 DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/
		 PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE )

# Store the library paths
file( WRITE "${CMAKE_SOURCE_DIR}/install_directory.txt"

	"${CMAKE_INSTALL_PREFIX}/include/rpi-hw\n"
	"${CMAKE_INSTALL_PREFIX}/share/doc/rpi-hw\n"
)

# Define the unistaller
add_custom_target( uninstall COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake )

