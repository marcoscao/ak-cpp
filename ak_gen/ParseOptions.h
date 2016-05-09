#ifndef AK_GENERATE_PARSER_OPTIONS__
#define AK_GENERATE_PARSER_OPTIONS__

#include "ak_core/ParseOptionsBase.h"
#include "ak_core/Factory.h"
#include "ak_core/LogSystem.h"
#include "ak_core/Visitor.h"

#include <memory>
#include <string>
#include <vector>


namespace ak {


  namespace gen {

   enum GenOptionsIDs {
      SOURCES_OP_ID = 100,
      HELP_OP_ID,
      VERBOSE_OP_ID,
      VERSION_OP_ID,
      MEDIA_OP_ID,
      CHUNK_NUMBER_OP_ID
   };


   AK_DEFINE_OPTION_WITH_MULTIPLE_VALUES( 
      SourcesOp, SOURCES_OP_ID, 
      "source-path,s", "source-path",
      "Sets source paths to iterate over. This option can be used multiple times", 
      std::string );
 
   AK_DEFINE_OPTION( 
      HelpOp, HELP_OP_ID, 
      "help,h", "help", 
      "Shows usage Help and available options" )

   AK_DEFINE_OPTION( 
      VerboseOp, VERBOSE_OP_ID, 
      "verbose", "verbose", 
      "Activate Verbose mode" ) 

   AK_DEFINE_OPTION( 
      VersionOp, VERSION_OP_ID, 
      "version,v", "version", 
      "Show current version info" ) 

   AK_DEFINE_OPTION_WITH_UNIQUE_VALUE( 
      MediaOp, MEDIA_OP_ID, 
      "media", "media", 
      "Media to search for", 
      std::string, "audio" ) 

   AK_DEFINE_OPTION_WITH_UNIQUE_VALUE( 
      ChunkNumberOp, CHUNK_NUMBER_OP_ID, 
      "chunk-number", "chunk number", 
      "Number of chunk files to process in a group. Default is 50", 
      int, 50 ) 




   class ParseOptions : public ParseOptionsBase {
   public:
      ParseOptions();

      // virtual void register_options( );

      virtual void execute();

   private:

      void show_current_settings_();
   };


} }

#endif


