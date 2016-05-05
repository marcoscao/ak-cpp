#include "ChunkOp.h"
#include "ak_core/LogSystem.h"

using namespace std;

namespace ak { namespace gen {

   Option * ChunkOp::create()
   {
      return new ChunkOp();
   }

   string ChunkOp::cmdline_id() 
   {
      return "media,m";
   }

   string ChunkOp::name() 
   {
      return "media";
   }

   string ChunkOp::description() 
   {
      return "Sets aprox. chunk size in bytes when doing operations";
   }

   ParseOptionsBase::StorageType * ChunkOp::storage_type() 
   {
      return ParseOptionsBase::set_unique< int >( &chunk_size_, 4096 );
   }

   void ChunkOp::execute( ParseOptionsBase const & ) 
   {
      LOG_CONSOLE("This is the Chunk size" )      
   }

   int ChunkOp::chunk_size() const
   {
      return chunk_size_;
   }

} }



