project(ak)

SET( CMAKE_CXX_FLAGS "-std=c++11" )

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory( core )
add_subdirectory( ak_generate )
add_subdirectory( ak_sync )
add_subdirectory( ak_query )

