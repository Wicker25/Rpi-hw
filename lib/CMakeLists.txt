# Project name
project( Dependencies )

# Set the minimum required version of CMake
cmake_minimum_required( VERSION 2.6 )

# Dependency directories
set( UTF8CPP_DIR ${PROJECT_SOURCE_DIR}/utf8-cpp )

message( "-- Using built-in UTF8-CPP library" )

# Define the library installer
install( DIRECTORY		${UTF8CPP_DIR}
		 DESTINATION	${CMAKE_INSTALL_PREFIX}/include )

# Store the library paths
file( APPEND "${RPI_HW_DIR}/install_directories.txt"

	"${CMAKE_INSTALL_PREFIX}/include/utf8-cpp\n"
)
