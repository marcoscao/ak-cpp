#include "SourcesOp.h"
#include "ParseOptions.h"

using namespace std;

namespace ak { namespace gen {
   SourcesOp::SourcesOp()
   : sources_paths_()
   {
   }

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

   void SourcesOp::execute( ParseOptionsBase const & pob ) {
      //LOG_CONSOLE("Great!! doing source-path stuff" )      
      LOG_I( "Executing Sources Command" )
   
      // for( auto i : sources_paths_ ) {
      //    LOG_I( "Iterating over source path", i );
      //    LOG_CONSOLE( "\nIterating over source path", i + "..." );
      // }
   }

   const SourcesOp::SourcesCt & SourcesOp::sources() const
   {
      return sources_paths_;
   }

} }



