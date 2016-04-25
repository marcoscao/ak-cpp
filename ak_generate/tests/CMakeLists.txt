
include_directories( "${PROJECT_SOURCE_DIR}")

set( SOURCES
   ../ProgramOptions.cpp
   ../SourcesCmd.cpp
   test_sources_op.cpp
)

add_executable( test_sources_option ${SOURCES} )

target_link_libraries( test_sources_option akcore ${AK_BOOST_TEST_LIB} )

install( TARGETS test_sources_option DESTINATION bin/tests )
#install( FILES "${PROJECT_BINARY_DIR}/version.h" DESTINATION include )


