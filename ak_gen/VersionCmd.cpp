#include "VersionCmd.h"
#include "ak_core/LogSystem.h"
#include "ak_core/ParseOptionsBase.h"
#include "ak_core/LogSystem.h"

using namespace std;

namespace ak { namespace gen {

   VersionCmd::VersionCmd()
   {
   }

   Command * VersionCmd::create()
   {
      return new VersionCmd();
   }

   void VersionCmd::execute( ParseOptionsBase const & pob ) 
   {
      LOG_CONSOLE("ak_gen ver. 2016.05.001" )      
      LOG_CONSOLE("Built on May 2016" )      
      LOG_CONSOLE("(c) m.santamaria" )      
   }

} }



