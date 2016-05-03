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
         };

         ParseOptions();

         virtual void register_options( factory<Option> & );

         virtual void execute();


      private:

         void show_current_settings_();

      };


} }

#endif

