
include_directories( "${PROJECT_SOURCE_DIR}/core")

set( SOURCES
	CreateXmlMasterCmd.cpp
	main.cpp
)

add_executable( ak_generate ${SOURCES} )

target_link_libraries( ak_generate akcore )

install( TARGETS ak_generate DESTINATION bin )
#install( FILES "${PROJECT_BINARY_DIR}/version.h" DESTINATION include )


