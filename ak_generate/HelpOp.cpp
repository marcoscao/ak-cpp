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

   void HelpOp::execute() {
      LOG_CONSOLE("Great!! Showing HELP" )      
   }

} }



