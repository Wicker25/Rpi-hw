# Project name
project( RpiHw )

# Set the minimum required version of CMake
cmake_minimum_required( VERSION 2.6 )

# Set the version of the library
set( RPI_HW_VERSION			"0.3.0" )
set( RPI_HW_VERSION_MAJOR	0 )
set( RPI_HW_VERSION_MINOR	3 )
set( RPI_HW_VERSION_PATCH	0 )

# Project directories
set( RPI_HW_DIR					${PROJECT_SOURCE_DIR}	)
set( RPI_HW_SOURCE_DIR 			${RPI_HW_DIR}/src		)
set( RPI_HW_INCLUDE_DIR			${RPI_HW_DIR}/include	)
set( RPI_HW_LIBRARY_DIR			${RPI_HW_DIR}/lib		)
set( RPI_HW_BUILD_DIR 			${RPI_HW_DIR}/build		)
set( RPI_HW_DOXYGEN_DIR 		${RPI_HW_DIR}/doxygen	)
set( RPI_HW_CMAKE_DIR 			${RPI_HW_DIR}/cmake		)
set( RPI_HW_PKGCONFIG_DIR 		${RPI_HW_DIR}/pkgconfig	)

# Set the output directories
set( LIBRARY_OUTPUT_PATH		${RPI_HW_BUILD_DIR} )
set( EXECUTABLE_OUTPUT_PATH		${RPI_HW_BUILD_DIR} )

# Set the CMake's module path
set( CMAKE_MODULE_PATH	${CMAKE_MODULE_PATH} ${RPI_HW_DIR}/cmake )
set( CMAKE_MODULES		UTF8-CPP )

# Set the compiler flags
add_definitions( -Wall -ansi -pedantic -pedantic-errors -Wno-long-long ) # -Wno-psabi

# Remove temporary files
execute_process( COMMAND ${CMAKE_COMMAND} -E remove "${RPI_HW_DIR}/install_directories.txt" )


# Check if RPi's Revision has been specified by user
if ( RPI_REVISION )
	message( "-- Using Raspberry Pi Revision Number: ${RPI_REVISION}" )
else()
	# Else find it with an automated script
	# grep -Po '^Revision\s*:\s*\K[[:xdigit:]]{7}' /proc/cpuinfo
	execute_process( COMMAND grep -Po "^Revision\\s*:\\s*\\K[[:xdigit:]]+" /proc/cpuinfo
					 OUTPUT_VARIABLE RPI_REVISION )

	# If have not found the Revision number, use the last version
	if ( RPI_REVISION )
		message( "-- Detecting Raspberry Pi Revision Number: ${RPI_REVISION}" )
	else()
		set( RPI_REVISION "0006" )
		message( WARNING "-- Could NOT find Raspberry Pi revision!" )
	endif()

	set( RPI_REVISION "0x${RPI_REVISION}" )
endif()


# Find some dependencies
find_package( Threads REQUIRED )
find_package( UTF8-CPP )

# If I couldn't find the UTF8-CPP library, use the built-in source
if ( NOT UTF8-CPP_FOUND )
	add_subdirectory( lib )
endif()

# Set the include directories
include_directories(

	${RPI_HW_INCLUDE_DIR}
	${RPI_HW_LIBRARY_DIR}/utf8-cpp
)

# Define some options
option( USE_FREETYPE	"Use FreeType library"	ON )
option( USE_MAGICK		"Use GraphicsMagick++ library"	ON )

# Enable/disable FreeType support
if ( USE_FREETYPE )
	find_package( Freetype REQUIRED )
	include_directories( ${FREETYPE_INCLUDE_DIRS} )

	set( CMAKE_MODULES ${CMAKE_MODULES} Freetype )

	set( USE_FREETYPE 1 )
else()
	set( USE_FREETYPE 0 )
endif()

# Enable/disable GraphicsMagick++ support
if ( USE_MAGICK )
	find_package( GraphicsMagick++ REQUIRED )
	include_directories( ${GraphicsMagick++_INCLUDE_DIRS} )

	set( CMAKE_MODULES ${CMAKE_MODULES} GraphicsMagick++ )

	set( USE_MAGICK 1 )
else()
	set( USE_MAGICK 0 )
endif()


# Define the list of files to be built dynamically
configure_file(

	${RPI_HW_INCLUDE_DIR}/rpi-hw/version.hpp.in
	${RPI_HW_INCLUDE_DIR}/rpi-hw/version.hpp
	IMMEDIATE @ONLY
)

configure_file(

	${RPI_HW_INCLUDE_DIR}/rpi-hw/config.hpp.in
	${RPI_HW_INCLUDE_DIR}/rpi-hw/config.hpp
	IMMEDIATE @ONLY
)

configure_file(

	${RPI_HW_INCLUDE_DIR}/rpi-hw/rpi.hpp.in
	${RPI_HW_INCLUDE_DIR}/rpi-hw/rpi.hpp
	IMMEDIATE @ONLY
)

configure_file(

	${RPI_HW_PKGCONFIG_DIR}/rpi-hw.pc.in
	${RPI_HW_PKGCONFIG_DIR}/rpi-hw.pc
	IMMEDIATE @ONLY
)

configure_file(

	${RPI_HW_DOXYGEN_DIR}/doxy.conf.in
	${RPI_HW_DOXYGEN_DIR}/doxy.conf
	IMMEDIATE @ONLY
)

configure_file(

	${RPI_HW_DIR}/cmake_uninstall.cmake.in
	${RPI_HW_DIR}/cmake_uninstall.cmake
	IMMEDIATE @ONLY
)

# Build the library
add_library( rpihw SHARED

	${RPI_HW_SOURCE_DIR}/utils.cpp
	${RPI_HW_SOURCE_DIR}/time.cpp
	${RPI_HW_SOURCE_DIR}/mutex.cpp
	${RPI_HW_SOURCE_DIR}/gpio.cpp

	${RPI_HW_SOURCE_DIR}/bitset.cpp
	${RPI_HW_SOURCE_DIR}/unicode.cpp

	${RPI_HW_SOURCE_DIR}/iface/base.cpp
	${RPI_HW_SOURCE_DIR}/iface/output.cpp
	${RPI_HW_SOURCE_DIR}/iface/input.cpp
	${RPI_HW_SOURCE_DIR}/iface/shift-base.cpp
	${RPI_HW_SOURCE_DIR}/iface/shift-out.cpp
	${RPI_HW_SOURCE_DIR}/iface/shift-in.cpp
	${RPI_HW_SOURCE_DIR}/iface/encoder-out.cpp
	${RPI_HW_SOURCE_DIR}/iface/encoder-in.cpp
	${RPI_HW_SOURCE_DIR}/iface/decoder-out.cpp
	${RPI_HW_SOURCE_DIR}/iface/decoder-in.cpp

	${RPI_HW_SOURCE_DIR}/font/freetype.cpp

	${RPI_HW_SOURCE_DIR}/keypad/base.cpp
	${RPI_HW_SOURCE_DIR}/keypad/matrix.cpp

	${RPI_HW_SOURCE_DIR}/display/s7seg.cpp
	${RPI_HW_SOURCE_DIR}/display/m7seg.cpp
	${RPI_HW_SOURCE_DIR}/display/hd44780.cpp
	${RPI_HW_SOURCE_DIR}/display/pcd8544.cpp

	${RPI_HW_SOURCE_DIR}/motor/stepper.cpp
)


# Link external libraries
target_link_libraries( rpihw ${CMAKE_THREAD_LIBS_INIT} )
target_link_libraries( rpihw rt )

if ( USE_FREETYPE )
	target_link_libraries( rpihw ${FREETYPE_LIBRARIES} )
endif()

if ( USE_MAGICK )
	target_link_libraries( rpihw ${GraphicsMagick++_LIBRARIES} )
endif()


# Build the executables
add_executable( rpi-gpio ${RPI_HW_SOURCE_DIR}/rpi-gpio.cpp )
target_link_libraries( rpi-gpio rpihw )


# If Doxygen was found, define the function `make doc` to build the local documentation
find_package( Doxygen )

if ( DOXYGEN_FOUND )
	add_custom_target( doc COMMAND doxygen doxygen/doxy.conf )
	add_custom_target( doc-clean COMMAND rm -R "${RPI_HW_DIR}/doc" )
endif ( DOXYGEN_FOUND )


# Define the library installer
install_targets( /lib rpihw )

install( FILES			${RPI_HW_INCLUDE_DIR}/rpi-hw.hpp
		 DESTINATION	${CMAKE_INSTALL_PREFIX}/include )

install( DIRECTORY		${RPI_HW_INCLUDE_DIR}/rpi-hw
		 DESTINATION	${CMAKE_INSTALL_PREFIX}/include
		 FILES_MATCHING
		 PATTERN "*"
		 PATTERN "*.in" EXCLUDE )

# Define the pkg-config installer
install( FILES			${RPI_HW_PKGCONFIG_DIR}/rpi-hw.pc
		 DESTINATION	${CMAKE_INSTALL_PREFIX}/lib/pkgconfig )

# Define the CMake's modules installer
install( FILES			${RPI_HW_CMAKE_DIR}/FindRpiHw.cmake
		 DESTINATION	${CMAKE_ROOT}/Modules/ )

foreach ( module ${CMAKE_MODULES} )
	if ( NOT EXISTS "${CMAKE_ROOT}/Modules/Find${module}.cmake" )
		install( FILES			${RPI_HW_CMAKE_DIR}/Find${module}.cmake
				 DESTINATION	${CMAKE_ROOT}/Modules/ )
	endif()
endforeach()

# Define the tools installer
install( FILES ${RPI_HW_BUILD_DIR}/rpi-gpio
		 DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/
		 PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE )

# Store the library paths
file( APPEND "${RPI_HW_DIR}/install_directories.txt"

	"${CMAKE_INSTALL_PREFIX}/include/rpi-hw\n"
	"${CMAKE_INSTALL_PREFIX}/share/doc/rpi-hw\n"
)

# Define the unistaller command
add_custom_target( uninstall COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake )
