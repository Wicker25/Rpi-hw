# Join a list

function( join OUTPUT VALUES )
  string( REPLACE ";" " " TMP "${VALUES}" )
  set( ${OUTPUT} "${TMP}" PARENT_SCOPE )
endfunction()


# Try to find Raspberry Pi Revision

function( findRpiRevision OUTPUT )
	# Find it with an automated script
	execute_process( COMMAND grep -Po "^Revision\\s*:\\s*\\K[[:xdigit:]]+" /proc/cpuinfo OUTPUT_VARIABLE TMP )

	# If have not found the Revision number, use the last version
	if ( TMP )
		message( "-- Detecting Raspberry Pi Revision Number: ${TMP}" )
	else()
		set( TMP "0006" )
		message( WARNING "-- Could NOT find Raspberry Pi revision!" )
	endif()

	set( ${OUTPUT} "0x${TMP}" PARENT_SCOPE )
endfunction()


# Add pkg-config's `cflags` using paths to the headers

function( addPkgConfigCflags OUTPUT INCLUDE_DIRS )
	foreach( DIR ${INCLUDE_DIRS} )
		list( APPEND TMP "-I${DIR}" )
	endforeach()

	set( ${OUTPUT} ${${OUTPUT}} ${TMP} PARENT_SCOPE )
endfunction()


# Add pkg-config's `libs` using paths of the libraries

function( addPkgConfigLibs OUTPUT LIBRARIES )
	foreach( LIB "${LIBRARIES}" )
		string( REGEX REPLACE "^(.+)?/lib(.+)?\\.(so|a)$" "-L\\1 -l\\2" LIB ${LIB} )
		list( APPEND TMP ${LIB} )
	endforeach()

	set( ${OUTPUT} ${${OUTPUT}} ${TMP} PARENT_SCOPE )
endfunction()
