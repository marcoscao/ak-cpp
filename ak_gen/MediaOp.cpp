#include "MediaOp.h"
#include "ak_core/LogSystem.h"

using namespace std;

namespace ak { namespace gen {

   Option * MediaOp::create()
   {
      return new MediaOp();
   }

   string MediaOp::cmdline_id() 
   {
      return "media,m";
   }

   string MediaOp::name() 
   {
      return "media";
   }

   string MediaOp::description() 
   {
      return "Sets media type work mode. Default media is 'audio'. \
         Available modes are: 'audio', 'lyrics', 'art', 'video' ";
   }

   ParseOptionsBase::StorageType * MediaOp::storage_type() 
   {
      return ParseOptionsBase::set_unique< string >( &media_, "audio" );
   }

   void MediaOp::execute( ParseOptionsBase const & ) 
   {
      LOG_CONSOLE("Verifying that entered media is supported" )      
   }

   std::string MediaOp::media() const
   {
      return media_;
   }

} }



