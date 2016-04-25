
include_directories( "${PROJECT_SOURCE_DIR}")

set( SOURCES
         CreateXmlCmd.cpp
	 main.cpp
         ProgramOptions.cpp
	 SourcesCmd.cpp
)

add_executable( ak_generate ${SOURCES} )

target_link_libraries( ak_generate akcore )

install( TARGETS ak_generate DESTINATION bin )
#install( FILES "${PROJECT_BINARY_DIR}/version.h" DESTINATION include )


add_subdirectory( tests )

