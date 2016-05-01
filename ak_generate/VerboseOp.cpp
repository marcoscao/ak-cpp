#include "VerboseOp.h"

using namespace std;

namespace ak { namespace gen {

   Option * VerboseOp::create()
   {
      return new VerboseOp();
   }

   string VerboseOp::cmdline_id() {
      return "verbose";
   }

   string VerboseOp::name() {
      return "verbose";
   }

   string VerboseOp::description() {
      return "Displays more detailed information";
   }

   ParseOptionsBase::StorageType * VerboseOp::storage_type() {
      return nullptr;
   }

   void VerboseOp::execute() {
      LOG_CONSOLE("Great!! Entering verbose mode" )      
   }

} }



