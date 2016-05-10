
include_directories( "${PROJECT_SOURCE_DIR}")

set( SOURCES
   CollectDataCmd.cpp
   GenOptions.cpp
   HelpCmd.cpp
   main.cpp
   ParseOptions.cpp
   VersionCmd.cpp
)

add_executable( ak_gen ${SOURCES} )

target_link_libraries( ak_gen akcore )

install( TARGETS ak_gen DESTINATION bin )
#install( FILES "${PROJECT_BINARY_DIR}/version.h" DESTINATION include )


add_subdirectory( tests )

