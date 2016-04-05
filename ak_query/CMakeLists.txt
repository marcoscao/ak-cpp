
include_directories( "${PROJECT_SOURCE_DIR}/core")

add_executable( ak_query main.cpp )

target_link_libraries( ak_query akcore )

install( TARGETS ak_query DESTINATION bin )
#install( FILES "${PROJECT_BINARY_DIR}/version.h" DESTINATION include )


