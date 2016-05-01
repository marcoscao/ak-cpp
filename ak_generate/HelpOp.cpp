#include "HelpOp.h"

using namespace std;

namespace ak { namespace gen {

   Option * HelpOp::create()
   {
      return new HelpOp();
   }

   string HelpOp::cmdline_id() {
      return "help,h";
   }

   string HelpOp::name() {
      return "help";
   }

   string HelpOp::description() {
      return "Shows usage help and available options";
   }

   ParseOptionsBase::StorageType * HelpOp::storage_type() {
      return nullptr;
   }

   void HelpOp::execute( ParseOptionsBase const & pob ) {
      LOG_CONSOLE("");
      LOG_CONSOLE("   usage  ak_generate -s PATH_1 [ -s PATH_2 -s PATH_3 ... ] [ --verbose ] [ --dry-run ]");
      LOG_CONSOLE("");
      LOG_CONSOLE("   # example 1: Copyng from different sources in verbose mode\n")
      LOG_CONSOLE("   ak_generate -s /Vol/media/a -s /Vol/media/d --verbose")
      LOG_CONSOLE("\n");

      pob.print_usage( "" );
   }

} }



