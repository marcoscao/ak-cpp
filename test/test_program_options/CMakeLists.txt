
include_directories( "${PROJECT_SOURCE_DIR}")

set(  SOURCES
      main.cpp
#      test_program_options.cpp
)

add_executable( test_program_options ${SOURCES} )

target_link_libraries( test_program_options akcore )

install( TARGETS test_program_options DESTINATION bin )
#install( FILES "${PROJECT_BINARY_DIR}/version.h" DESTINATION include )


