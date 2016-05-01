#include "VersionOp.h"

using namespace std;

namespace ak { namespace gen {

   Option * VersionOp::create()
   {
      return new VersionOp();
   }

   string VersionOp::cmdline_id() {
      return "version";
   }

   string VersionOp::name() {
      return "version";
   }

   string VersionOp::description() {
      return "Shows current version";
   }

   ParseOptionsBase::StorageType * VersionOp::storage_type() {
      return nullptr;
   }

   void VersionOp::execute( ParseOptionsBase const & ) {
      LOG_CONSOLE("ak_generate ver. 2016.05.001  (c) mscao 2016" )      
   }

   void VersionOp::detailed() 
   {
      LOG_CONSOLE("ak_generate ver. 2016.05.001" )      
      LOG_CONSOLE("Built on May 2016" )      
      LOG_CONSOLE("(c) m.santamaria" )      
   }

} }



