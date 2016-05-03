
include_directories( "${PROJECT_SOURCE_DIR}")

set( SOURCES
   ../CollectDataCmd.cpp
   ../HelpOp.cpp
   ../MediaOp.cpp
   ../ParseOptions.cpp
   ../SourcesOp.cpp
   ../VerboseOp.cpp
   ../VersionOp.cpp
   test_options.cpp
)

add_executable( test_options ${SOURCES} )

target_link_libraries( test_options akcore ${AK_BOOST_TEST_LIB} )

add_test(   
   NAME test_options
   WORKING_DIRECTORY ${AK_TESTS_OUTPUT_DIR}
   COMMAND ${AK_TESTS_OUTPUT_DIR}/test_options
)

install( TARGETS test_options DESTINATION bin/tests )
#install( FILES "${PROJECT_BINARY_DIR}/version.h" DESTINATION include )


add_custom_command( 
   TARGET test_options
   POST_BUILD
   COMMAND ctest -C $<CONFIGURATION> --output-on-failure
)

