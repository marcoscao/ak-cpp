
include_directories( "${PROJECT_SOURCE_DIR}")

set(  SOURCES
      test_program_options.cpp
)

add_executable( test_program_options ${SOURCES} )

target_link_libraries( test_program_options akcore boost_program_options-mt.dylib )

install( TARGETS test_program_options DESTINATION bin )
#install( FILES "${PROJECT_BINARY_DIR}/version.h" DESTINATION include )


