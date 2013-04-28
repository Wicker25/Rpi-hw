# - Try to find UTF8-CPP library
#
# UTF8-CPP_FOUND		- TRUE if all components are found.
# UTF8-CPP_INCLUDE_DIRS	- Full paths to all include dirs.
#

# Find the header files
find_path( UTF8-CPP_INCLUDE_DIR NAMES utf8.h PATHS

	/usr/include/utf8-cpp
	/usr/include/utf8cpp
	/usr/include/UTF8-CPP
	/usr/include/UTF8CPP

	/usr/local/include/utf8-cpp
	/usr/local/include/utf8cpp
	/usr/local/include/UTF8-CPP
	/usr/local/include/UTF8CPP
)

# Process the data
include( FindPackageHandleStandardArgs )

find_package_handle_standard_args(

	UTF8-CPP
	REQUIRED_VARS	UTF8-CPP_INCLUDE_DIR
	VERSION_VAR		UTF8-CPP_VERSION
)

if ( UTF8-CPP_FOUND )
	# Build the variables
	set( UTF8-CPP_INCLUDE_DIRS ${UTF8-CPP_INCLUDE_DIR} )
endif()

mark_as_advanced( ${UTF8-CPP_INCLUDE_DIR} )
