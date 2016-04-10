set( SOURCES
   BaseCmd.cpp
   FileManager.cpp
   ProgramOptionsBase.cpp
   XmlManager.cpp
)

add_library( akcore SHARED ${SOURCES} )

target_link_libraries( akcore boost_program_options-mt )

install( TARGETS akcore DESTINATION bin )
install( FILES FileManager.h DESTINATION include )


