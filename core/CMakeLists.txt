set( SOURCES
	FileManager.cpp
	XmlManager.cpp
	BaseCmd.cpp
)

add_library( akcore ${SOURCES} )


install( TARGETS akcore DESTINATION bin )
install( FILES FileManager.h DESTINATION include )


