include_directories( "${SQLITE3_INCLUDE_DIRS}")

set( SOURCES
   AppManager.cpp
   Exception.cpp
   FileSystem.cpp
   Option.cpp
   ParseOptionsBase.cpp
   SqlSystem.cpp
   Utils.cpp
   XmlManager.cpp
)

add_library( akcore SHARED ${SOURCES} )

target_link_libraries( akcore ${AK_BOOST_PROGRAM_OPTIONS_LIB} ${SQLITE3_LIBRARIES})

install( TARGETS akcore DESTINATION bin )
install( FILES FileManager.h DESTINATION include )


