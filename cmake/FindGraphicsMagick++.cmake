# - Try to find Magick++ API (using GraphicsMagick++)
#
# GraphicsMagick++_FOUND			- TRUE if all components are found.
# GraphicsMagick++_INCLUDE_DIRS		- Full paths to all include dirs.
# GraphicsMagick++_LIBRARIES		- Full paths to all libraries.
# GraphicsMagick++_VERSION			- Version of the library.
#

# Find the header files
find_path( GraphicsMagick++_INCLUDE_DIR NAMES Magick++.h PATHS

	/usr/include/GraphicsMagick
	/usr/include/graphicsmagick
	/usr/local/include/GraphicsMagick
	/usr/local/include/graphicsmagick
)

# Find the library
find_library( GraphicsMagick++_LIBRARY NAMES GraphicsMagick++ )

# Find the version of the library
if ( GraphicsMagick++_INCLUDE_DIR AND EXISTS "${GraphicsMagick++_INCLUDE_DIR}/magick/version.h" )

	file(	STRINGS	"${GraphicsMagick++_INCLUDE_DIR}/magick/version.h" GraphicsMagick++_VERSION
			REGEX	"^#define MagickLibVersionText[\t ]+\".+\"$" )

	string( REGEX REPLACE "^#define MagickLibVersionText[\t ]+\"(.+)\"$" "\\1" GraphicsMagick++_VERSION ${GraphicsMagick++_VERSION} )
endif()

# Process the data
include( FindPackageHandleStandardArgs )

find_package_handle_standard_args(

	GraphicsMagick++
	REQUIRED_VARS	GraphicsMagick++_LIBRARY GraphicsMagick++_INCLUDE_DIR
	VERSION_VAR		GraphicsMagick++_VERSION
)

if ( GRAPHICSMAGICK++_FOUND )
	# Build the variables
	set( GraphicsMagick++_FOUND			${GRAPHICSMAGICK++_FOUND} )
	set( GraphicsMagick++_INCLUDE_DIRS	${GraphicsMagick++_INCLUDE_DIR} )
	set( GraphicsMagick++_LIBRARIES		${GraphicsMagick++_LIBRARY} )
endif()

mark_as_advanced(

	${GRAPHICSMAGICK++_FOUND}
	${GraphicsMagick++_INCLUDE_DIR}
	${GraphicsMagick++_LIBRARY}
)
