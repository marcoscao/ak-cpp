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

find_package( boost REQUIRED COMPONENTS program_options date_time )

include_directories( ${Boost_INCLUDE_DIR} )
link_directories( ${Boost_LIBRARY_DIRS} )


if( ${CYGWIN} )
   set(AK_BOOST_PROGRAM_OPTIONS_LIB 
	    boost_program_options 
	    boost_system 
	    boost_date_time 
	    boost_filesystem )

   set( AK_BOOST_TEST_LIB 
            boost_unit_test_framework )
endif()


if( ${APPLE} )
   set( AK_BOOST_PROGRAM_OPTIONS_LIB 
	    boost_program_options-mt
	    boost_date_time-mt 
	    boost_system-mt 
	    boost_filesystem-mt )
   
   set( AK_BOOST_TEST_LIB 
            boost_unit_test_framework-mt )

endif()


message( "* ak: boost include dirs: ${Boost_INCLUDE_DIR}" )
message( "* ak: boost library dirs: ${Boost_LIBRARY_DIRS}" )
message( "* ak: boost program_options found: ${Boost_PROGRAM_OPTIONS_FOUND}" )
message( "* ak: AK_BOOST_PROGRAM_OPTIONS_LIB : ${AK_BOOST_PROGRAM_OPTIONS_LIB}" )


add_subdirectory( ak_core )
add_subdirectory( ak_generate )
add_subdirectory( ak_sync )
add_subdirectory( ak_query )

