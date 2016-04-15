set( SOURCES
   BaseCmd.cpp
   FileManager.cpp
   ProgramOptionsBase.cpp
   XmlManager.cpp
)

add_library( akcore SHARED ${SOURCES} )

target_link_libraries( akcore ${AK_BOOST_PROGRAM_OPTIONS_LIB} )

install( TARGETS akcore DESTINATION bin )
install( FILES FileManager.h DESTINATION include )


