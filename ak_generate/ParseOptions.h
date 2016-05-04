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
//AK_CLASS_OPTION( VerboseOp, 101, "verbose", "verbose", "desc verb" ) 
   

   namespace gen {

      class ParseOptions : public ParseOptionsBase {
      public:
         
         enum OptionsIds {
            SOURCES_OP_ID = 100,
            HELP_OP_ID,
            VERBOSE_OP_ID,
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

