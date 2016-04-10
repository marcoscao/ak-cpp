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

message( "boost include dirs: ${Boost_INCLUDE_DIR}" )
message( "boost library dirs: ${Boost_LIBRARY_DIRS}" )

add_subdirectory( ak_core )
add_subdirectory( ak_generate )
add_subdirectory( ak_sync )
add_subdirectory( ak_query )
add_subdirectory( test )

