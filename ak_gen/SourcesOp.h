#ifndef AK_GEN_SOURCES_OP_H__
#define AK_GEN_SOURCES_OP_H__

#include "ak_core/FileSystem.h"
#include "ak_core/LogSystem.h"
#include "ak_core/Option.h"
#include "ak_core/ParseOptionsBase.h"

#include <iostream>
#include <string>

namespace ak { namespace gen {

   class SourcesOp : public ak::UserOption {
   public:

      //! Holds passed source paths through command line
      using SourcesCt = std::vector< std::string >;

      SourcesOp();

      static Option * create();

      virtual std::string cmdline_id();

      virtual std::string name();

      virtual std::string description();

      virtual ParseOptionsBase::StorageType * storage_type();

      virtual void execute( ParseOptionsBase const & );

      const SourcesCt & sources() const;

   private:
      SourcesCt sources_paths_;
   };


} }


#endif

