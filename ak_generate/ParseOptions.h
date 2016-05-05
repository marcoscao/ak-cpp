#ifndef AK_GENERATE_PARSER_OPTIONS__
#define AK_GENERATE_PARSER_OPTIONS__

#include "ak_core/Factory.h"
#include "ak_core/ParseOptionsBase.h"
#include "ak_core/LogSystem.h"

#include <memory>
#include <string>
#include <vector>


namespace ak {

   class Option;

//AK_CLASS_OPTION( CLASS_NAME, ID, CMDLINE_ID, NAME, DESC, VAR_TYPE, VAR_DEFAULT_VALUE ) 
//AK_CLASS_OPTION( MediaOp, 100, "media-type", "media", "desc media", std::string, "audio" ) 

  namespace gen {

	  enum GenOptionsIDs {
		  SOURCES_OP_ID = 100,
		  HELP_OP_ID,
	  };

//AK_MULTIPLE_OPTION( SourcesOp, 100, "source-path,s", "sources", "Sources desc", std::string ) 
AK_DEFINE_OPTION_MULTIPLE( SourcesOp, SOURCES_OP_ID, "source-path,s", "sources", "Sources desc", std::string ) 
//AK_DEFINE_OPTION_MULTIPLE( HelpOp, HRLP_OP_ID, "help,h", "help", "Help" ) 


      class ParseOptions : public ParseOptionsBase {
      public:
         
         enum OptionsIds {
            //SOURCES_OP_ID = 100,
            HELP_OP_ID = 101,
            VERBOSE_OP_ID = 102,
            VERSION_OP_ID,
            MEDIA_OP_ID,                  // "audio", "art", "lyrics", "video", "partitures", ...
            //MEDIA_MODE_OP_ID,             // "default", "all", "customized"
            //MEDIA_FILES_TYPES_OP_ID       // "flac;mp3;aiff;wav;"
            CHUNK_SIZE_OP_ID,             // chunk size
         };

         ParseOptions();

         virtual void register_options( factory<Option> & );

         virtual void execute();


      private:

         void show_current_settings_();

      };


} }

#endif

