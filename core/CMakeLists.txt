set( SOURCES
      BaseCmd.cpp
      FileManager.cpp
      ProgramOptionsBase.cpp
      XmlManager.cpp
)

add_library( akcore ${SOURCES} )


install( TARGETS akcore DESTINATION bin )
install( FILES FileManager.h DESTINATION include )


