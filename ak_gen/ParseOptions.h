#ifndef AK_GENERATE_PARSER_OPTIONS__
#define AK_GENERATE_PARSER_OPTIONS__

#include "ak_core/ParseOptionsBase.h"


namespace ak {

  namespace gen {


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


