# Rpi-hw examples

# Set the minimum required version of CMake
cmake_minimum_required( VERSION 2.6 )

# Set the compiler flags
add_definitions( -Wall -ansi -pedantic -pedantic-errors -std=c++11 )

# Set the output directories
set( LIBRARY_OUTPUT_PATH		"build" )
set( EXECUTABLE_OUTPUT_PATH		"build" )

# Find the Rpi-hw library
find_package( RpiHw REQUIRED )

# Find some dependencies
find_package( Freetype REQUIRED )
find_package( GraphicsMagick++ REQUIRED )

# Set the path to the header files
include_directories( ${RpiHw_INCLUDE_DIRS} )

# Build all examples
add_executable( blink ${CMAKE_SOURCE_DIR}/blink.cpp )
target_link_libraries( blink ${RpiHw_LIBRARIES} )

add_executable( mcp23017 ${CMAKE_SOURCE_DIR}/driver/mcp23017.cpp )
target_link_libraries( mcp23017 ${RpiHw_LIBRARIES} )

add_executable( mcp23s17 ${CMAKE_SOURCE_DIR}/driver/mcp23s17.cpp )
target_link_libraries( mcp23s17 ${RpiHw_LIBRARIES} )

add_executable( s7seg ${CMAKE_SOURCE_DIR}/display/s7seg.cpp )
target_link_libraries( s7seg ${RpiHw_LIBRARIES} )

add_executable( m7seg0 ${CMAKE_SOURCE_DIR}/display/m7seg0.cpp )
target_link_libraries( m7seg0 ${RpiHw_LIBRARIES} )

add_executable( m7seg1 ${CMAKE_SOURCE_DIR}/display/m7seg1.cpp )
target_link_libraries( m7seg1 ${RpiHw_LIBRARIES} )

add_executable( lcd16x2 ${CMAKE_SOURCE_DIR}/display/lcd16x2.cpp )
target_link_libraries( lcd16x2 ${RpiHw_LIBRARIES} )

add_executable( lcd20x4demo ${CMAKE_SOURCE_DIR}/display/lcd20x4demo.cpp )
target_link_libraries( lcd20x4demo ${RpiHw_LIBRARIES} )

add_executable( pcd8544 ${CMAKE_SOURCE_DIR}/display/pcd8544.cpp )
target_link_libraries( pcd8544 ${RpiHw_LIBRARIES} )

add_executable( 12keys0 ${CMAKE_SOURCE_DIR}/keypad/12keys0.cpp )
target_link_libraries( 12keys0 ${RpiHw_LIBRARIES} )

add_executable( 12keys1 ${CMAKE_SOURCE_DIR}/keypad/12keys1.cpp )
target_link_libraries( 12keys1 ${RpiHw_LIBRARIES} )

add_executable( 16keys0 ${CMAKE_SOURCE_DIR}/keypad/16keys0.cpp )
target_link_libraries( 16keys0 ${RpiHw_LIBRARIES} )

add_executable( 16keys1 ${CMAKE_SOURCE_DIR}/keypad/16keys1.cpp )
target_link_libraries( 16keys1 ${RpiHw_LIBRARIES} )

add_executable( 16keys2 ${CMAKE_SOURCE_DIR}/keypad/16keys2.cpp )
target_link_libraries( 16keys2 ${RpiHw_LIBRARIES} )

add_executable( 28bjy48 ${CMAKE_SOURCE_DIR}/motor/28bjy48.cpp )
target_link_libraries( 28bjy48 ${RpiHw_LIBRARIES} )

add_executable( hcsr04 ${CMAKE_SOURCE_DIR}/sensor/hcsr04.cpp )
target_link_libraries( hcsr04 ${RpiHw_LIBRARIES} )
