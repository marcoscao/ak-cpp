# avoid warning message about definition of Win32 into cygwin
# it must be at the top or cmake_ required version greater than 2.8.4

set( CMAKE_LEGACY_CYGWIN_WIN32 0 )



cmake_minimum_required( VERSION 2.8 )

project(ak)


# clang
SET( CMAKE_CXX_COMPILER "g++" )

#gcc
#SET( CMAKE_CXX_COMPILER "g++-mp-4.9" )

SET( CMAKE_CXX_FLAGS "-std=c++11" )

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#find_package( boost COMPONENTS program_options REQUIRED )
find_package( boost )

include_directories( ${Boost_INCLUDE_DIR} )
link_directories( ${Boost_LIBRARY_DIRS} )


if( Boost_PROGRAM_OPTIONS_FOUND )
	message( "* ak: found boost program_options" )
	set(AK_BOOST_PROGRAM_OPTIONS_LIB_DEBUG ${Boost_PROGRAM_OPTIONS_LIBRARY_DEBUG})
elseif()
	message( "***** ak: Oops! Not found component program_options" )
endif()


message( "* ak: boost include dirs: ${Boost_INCLUDE_DIR}" )
message( "* ak: boost library dirs: ${Boost_LIBRARY_DIRS}" )
message( "* ak: boost program_options debug lib name: ${AK_BOOST_PROGRAM_OPTIONS_LIB_DEBUG}" )


add_subdirectory( ak_core )
add_subdirectory( ak_generate )
add_subdirectory( ak_sync )
add_subdirectory( ak_query )
add_subdirectory( test )

