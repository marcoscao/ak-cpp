#ifndef AK_GEN_VERSION_COMMAND_H__
#define AK_GEN_VERSION_COMMAND_H__

#include "ak_core/Command.h"


namespace ak { 
   
   class ParseOptionsBase;

   namespace gen {

   class VersionCmd : public ak::Command {
   public:

      VersionCmd();

      static Command * create();

      virtual void execute( ParseOptionsBase const & );

   };

} }


#endif

