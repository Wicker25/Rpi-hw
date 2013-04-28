# - Try to find Rpi-hw library
#
# RpiHw_FOUND			- TRUE if all components are found.
# RpiHw_INCLUDE_DIRS	- Full paths to all include dirs.
# RpiHw_LIBRARIES		- Full paths to all libraries.
# RpiHw_VERSION			- Version of the library.
#

# Find the header files
find_path( RpiHw_INCLUDE_DIR NAMES rpi-hw )

# Find the library
find_library( RpiHw_LIBRARY NAMES rpihw )

# Find the version of the library
if ( RpiHw_INCLUDE_DIR AND EXISTS "${RpiHw_INCLUDE_DIR}/rpi-hw/version.hpp" )

	file(	STRINGS	"${RpiHw_INCLUDE_DIR}/rpi-hw/version.hpp" RpiHw_VERSION
			REGEX	"^#define RPI_HW_VERSION[\t ]+\".+\"$" )

	string( REGEX REPLACE "^#define RPI_HW_VERSION[\t ]+\"(.+)\"$" "\\1" RpiHw_VERSION ${RpiHw_VERSION} )
endif()

# Process the data
include( FindPackageHandleStandardArgs )

find_package_handle_standard_args(

	RpiHw
	REQUIRED_VARS	RpiHw_LIBRARY RpiHw_INCLUDE_DIR
	VERSION_VAR		RpiHw_VERSION
)

if ( RPIHW_FOUND )

	# Find some dependencies
	find_package( UTF8-CPP )
	find_package( Freetype )
	find_package( GraphicsMagick++ )

	# Build the variables
	set( RpiHw_FOUND		${RPIHW_FOUND} )

	set( RpiHw_INCLUDE_DIRS	${RpiHw_INCLUDE_DIR}
							${UTF8-CPP_INCLUDE_DIRS}
							${FREETYPE_INCLUDE_DIRS}
							${GraphicsMagick++_INCLUDE_DIRS} )

	set( RpiHw_LIBRARIES	${RpiHw_LIBRARY} ${GraphicsMagick++_LIBRARIES} )
endif()

mark_as_advanced(

	${RpiHw_FOUND}
	${RpiHw_INCLUDE_DIR}
	${RpiHw_LIBRARY}
)
