
include_directories( "${PROJECT_SOURCE_DIR}/core")

add_executable( ak_sync main.cpp )

target_link_libraries( ak_sync akcore )

install( TARGETS ak_sync DESTINATION bin )
#install( FILES "${PROJECT_BINARY_DIR}/version.h" DESTINATION include )


