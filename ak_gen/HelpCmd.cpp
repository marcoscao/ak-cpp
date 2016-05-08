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
      LOG_CONSOLE("ak_gen (c) 2016");
      LOG_CONSOLE("usage: ak_gen [options] <inputs>");
      //LOG_CONSOLE("usage: ak_gen --source-path src_path ... [ --verbose ] [ --dry-run ] ");
      LOG_CONSOLE("");
      LOG_CONSOLE("notes:");
      LOG_CONSOLE("* a detailed log file will also be generated");
      LOG_CONSOLE("");
      LOG_CONSOLE("examples:");
      LOG_CONSOLE("1) ak_gen -s /Vol/media/a -s /Vol/media/d            # process multiple source paths")
      LOG_CONSOLE("2) ak_gen -s /Vol/media/a -s /Vol/media/d --verbose  # process multiple using verbose")
      LOG_CONSOLE("3) ak_gen -s /Vol/media/a -s --verbose --chunk-number 128  # process files in chunks of 128 items")

      LOG_CONSOLE("");

      pob.print_usage( "" );
   }

} }



