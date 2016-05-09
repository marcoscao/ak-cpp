#ifndef AK_GEN_HELP_COMMAND_H__
#define AK_GEN_HELP_COMMAND_H__

#include "ak_core/Command.h"

namespace ak { 
   
   class ParseOptionsBase;


   namespace gen {

   class HelpCmd : public ak::Command {
   public:

      HelpCmd();

      static Command * create();

      virtual void execute( ParseOptionsBase const & );

      //virtual void accept( VisitorCmd & );

   };

} }


#endif

