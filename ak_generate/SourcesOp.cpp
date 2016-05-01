#include "SourcesOp.h"

using namespace std;

namespace ak { namespace gen {


   Option * SourcesOp::create()
   {
      return new SourcesOp();
   }

   string SourcesOp::cmdline_id() {
      return "source-path,s";
   }

   string SourcesOp::name() {
      return "source-path";
   }

   string SourcesOp::description() {
      return "Sets source paths to iterate over. This option can be used multiple times";
   }

   ParseOptionsBase::StorageType * SourcesOp::storage_type() {
      return ParseOptionsBase::set_multiple< string >( &sources_paths_ );
   }

   void SourcesOp::execute() {
      LOG_CONSOLE("Great!! doing source-path stuff" )      
   }

   const SourcesOp::SourcesCt & SourcesOp::sources() const
   {
      return sources_paths_;
   }


} }



