#ifndef AK_GEN_CHUNK_OP_H__
#define AK_GEN_CHUNK_OP_H__

#include "ak_core/Option.h"
#include "ak_core/ParseOptionsBase.h"

#include <string>

namespace ak { namespace gen {

   class ChunkOp : public ak::UserOption {
   public:
      static Option * create();

      virtual std::string cmdline_id();

      virtual std::string name();

      virtual std::string description();

      virtual ParseOptionsBase::StorageType * storage_type();

      virtual void execute( ParseOptionsBase const & );

      std::string media() const;
 
   private:
      //! chunk size in bytes
      int chunk_size_;

   };

} }


#endif

