#ifndef AK_GEN_OPTIONS__
#define AK_GEN_OPTIONS__

#include "ak_core/OptionDef.h"

#include <string>

namespace ak {

  namespace gen {


   AK_DEFINE_OPTION_WITH_MULTIPLE_VALUES( 
      SourcesOp, 200, //SOURCES_OP_ID, 
      "source-path,s", "source-path",
      "Sets source paths to iterate over. This option can be used multiple times", 
      std::string )
 
   AK_DEFINE_OPTION( 
      HelpOp, 201, //HELP_OP_ID, 
      "help,h", "help", 
      "Shows usage Help and available options" )

   AK_DEFINE_OPTION( 
      VerboseOp, 202, 
      "verbose", "verbose", 
      "Activate Verbose mode" ) 

   AK_DEFINE_OPTION( 
      VersionOp, 203, 
      "version,v", "version", 
      "Show current version info" ) 

   AK_DEFINE_OPTION_WITH_UNIQUE_VALUE( 
      MediaOp, 204, 
      "media", "media", 
      "Media to search for", 
      std::string, "audio" ) 

   AK_DEFINE_OPTION_WITH_UNIQUE_VALUE( 
      ChunkNumberOp, 205, 
      "chunk-number", "chunk number", 
      "Number of chunk files to process in a group. Default is 50", 
      int, 50 ) 


} }

#endif


