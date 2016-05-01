#ifndef AK_GEN_VERSION_OP_H__
#define AK_GEN_VERSION_OP_H__

#include "ak_core/LogSystem.h"
#include "ak_core/Option.h"
#include "ak_core/ParseOptionsBase.h"

#include <iostream>
#include <string>

namespace ak { namespace gen {

   class VersionOp : public ak::UserOption {
   public:
      static Option * create();

      virtual std::string cmdline_id();

      virtual std::string name();

      virtual std::string description();

      virtual ParseOptionsBase::StorageType * storage_type();

      virtual void execute();
   };

} }


#endif

