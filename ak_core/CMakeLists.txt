set( SOURCES
   Command.cpp
   Exception.cpp
   FileSystem.cpp
   ProgramOptionsBase.cpp
   Utils.cpp
   XmlManager.cpp
)

add_library( akcore SHARED ${SOURCES} )

target_link_libraries( akcore ${AK_BOOST_PROGRAM_OPTIONS_LIB} boost_date_time-mt boost_system-mt boost_filesystem-mt )

install( TARGETS akcore DESTINATION bin )
install( FILES FileManager.h DESTINATION include )


