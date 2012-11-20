# CMake's configuration

# Nome del progetto
project( RpiHw )

# Vincolo sulle versioni minori di CMake
cmake_minimum_required( VERSION 2.6 )

# Imposto la versione della libreria
set( RPI_HW_VERSION_MAJOR 0 )
set( RPI_HW_VERSION_MINOR 2 )
set( RPI_HW_VERSION_PATCH 2 )

# Cerco le dipendenze necessarie
find_package( Threads )

# Aggiungo una direttiva al compilatore
add_definitions( -Wall -ansi -pedantic -pedantic-errors -Wno-psabi )

# Percorso degli headers
include_directories(

	${CMAKE_SOURCE_DIR}/include
	${CMAKE_BINARY_DIR}/include
)

# Ricavo alcune informazioni sul sistema
# cat /proc/cpuinfo | grep Revision | awk "{printf $3}"
execute_process( COMMAND cat /proc/cpuinfo
				 COMMAND grep Revision
				 COMMAND awk "{printf $3}"
				 OUTPUT_VARIABLE RPI_REVISION )

# Mi assicuro che sia stato trovato il numero di revisione del Raspberry Pi
# altrimenti suppongo che sia l'ultima versione della scheda
IF ( RPI_REVISION )

	# Log di lavoro
	MESSAGE( "-- Detecting Raspberry Pi revision: ${RPI_REVISION}" )

ELSE ( RPI_REVISION )

	set( RPI_REVISION "0006" )

	# Log di lavoro
	MESSAGE( WARNING "-- Could NOT find Raspberry Pi revision!" )

ENDIF ( RPI_REVISION )

# Imposto i file di configurazione generati automaticamente
configure_file(

	"${CMAKE_SOURCE_DIR}/include/rpi-hw/version.hpp.in"
	"${CMAKE_BINARY_DIR}/include/rpi-hw/version.hpp"
)

configure_file(

	"${CMAKE_SOURCE_DIR}/include/rpi-hw/rpi.hpp.in"
	"${CMAKE_BINARY_DIR}/include/rpi-hw/rpi.hpp"
)

# Imposto lo script per la disinstallazione
configure_file(

	"${CMAKE_SOURCE_DIR}/cmake_uninstall.cmake.in"
	"${CMAKE_BINARY_DIR}/cmake_uninstall.cmake"
	IMMEDIATE @ONLY
)

# Imposto la cartella delle librerie generate
set( LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib )
# Imposto la cartella dei binari generati
set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin )

# Modifico i percorsi dei sorgenti e dei binari
set( RPI_HW_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/src )
set( RPI_HW_BINARY_DIR ${CMAKE_BINARY_DIR}/bin ${CMAKE_BINARY_DIR}/bin )

# Libreria Rpi-hw
add_library( rpihw SHARED

	${RPI_HW_SOURCE_DIR}/utils.cpp
	${RPI_HW_SOURCE_DIR}/bitset.cpp
	${RPI_HW_SOURCE_DIR}/mutex.cpp
	${RPI_HW_SOURCE_DIR}/gpio.cpp
	${RPI_HW_SOURCE_DIR}/iface/base.cpp
	${RPI_HW_SOURCE_DIR}/iface/output.cpp
	${RPI_HW_SOURCE_DIR}/iface/input.cpp
	${RPI_HW_SOURCE_DIR}/iface/encoder.cpp
	${RPI_HW_SOURCE_DIR}/iface/decoder.cpp
	${RPI_HW_SOURCE_DIR}/keypad/base.cpp
	${RPI_HW_SOURCE_DIR}/keypad/matrix.cpp
	${RPI_HW_SOURCE_DIR}/display/s7seg.cpp
	${RPI_HW_SOURCE_DIR}/display/m7seg.cpp
	${RPI_HW_SOURCE_DIR}/display/hd44780.cpp
)

target_link_libraries( rpihw ${CMAKE_THREAD_LIBS_INIT} )


# Compilo gli eseguibili
add_executable( rpi-gpio ${RPI_HW_SOURCE_DIR}/rpi-gpio.cpp )
target_link_libraries( rpi-gpio rpihw )


# Installatore della libreria
install_targets( /lib rpihw )

# Installatore degli headers
install( FILES ${CMAKE_SOURCE_DIR}/include/rpi-hw.hpp
		 DESTINATION ${CMAKE_INSTALL_PREFIX}/include )

install( DIRECTORY ${CMAKE_SOURCE_DIR}/include/rpi-hw
		 DESTINATION ${CMAKE_INSTALL_PREFIX}/include
		 FILES_MATCHING
		 PATTERN "*"
		 PATTERN "*.in" EXCLUDE )

# Installatore delle informazioni per pkg-config
install( FILES ${CMAKE_SOURCE_DIR}/pkgconfig/rpi-hw.pc
		 DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig )

# Installatore delle informazioni per CMake
install( FILES ${CMAKE_SOURCE_DIR}/cmake/FindRpiHw.cmake
		 DESTINATION ${CMAKE_ROOT}/Modules/ )

# Installatore degli eseguibili
install( FILES ${CMAKE_SOURCE_DIR}/bin/rpi-gpio
		 DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/
		 PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE )

# Memorizzo le cartelle di destinazione
file( WRITE "${CMAKE_SOURCE_DIR}/install_directory.txt"

	"${CMAKE_INSTALL_PREFIX}/include/rpi-hw\n"
	"${CMAKE_INSTALL_PREFIX}/share/doc/rpi-hw\n"
)

# Aggiungo il "make uninstall"
add_custom_target( uninstall COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake )

