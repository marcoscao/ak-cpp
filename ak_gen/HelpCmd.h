#ifndef AK_GEN_HELP_COMMAND_H__
#define AK_GEN_HELP_COMMAND_H__

#include "ak_core/FileSystem.h"
#include "ak_core/Command.h"
#include "ak_core/ParseOptionsBase.h"

#include <iostream>
#include <string>

namespace ak { namespace gen {

   class HelpCmd : public ak::Command {
   public:

      HelpCmd();

      static Command * create();

      virtual void execute( ParseOptionsBase const & );

      //virtual void accept( VisitorCmd & );

   };

} }


#endif

