#include "HelpCmd.h"
#include "ak_core/LogSystem.h"
#include "ParseOptions.h"

using namespace std;

namespace ak { namespace gen {

   HelpCmd::HelpCmd()
   {
   }

   Command * HelpCmd::create()
   {
      return new HelpCmd();
   }

   void HelpCmd::execute( ParseOptionsBase const & pob ) 
   {
      LOG_CONSOLE("");
      LOG_CONSOLE("   usage  ak_gen -s PATH_1 [ -s PATH_2 -s PATH_3 ... ] [ --verbose ] [ --dry-run ] [--media=audio/art/lyrics/video]");
      LOG_CONSOLE("");
      LOG_CONSOLE("   # example 1: Copyng from different sources in verbose mode\n")
      LOG_CONSOLE("   ak_gen -s /Vol/media/a -s /Vol/media/d --verbose [--media=audio] ")
      LOG_CONSOLE("\n");

      pob.print_usage( "" );
   }

} }



