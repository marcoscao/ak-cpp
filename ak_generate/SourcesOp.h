#ifndef AK_GEN_SOURCES_OP_H__
#define AK_GEN_SOURCES_OP_H__

#include "ak_core/Option.h"
#include "ak_core/ParseOptionsBase.h"

#include <iostream>
#include <string>

using namespace std;

namespace ak {
namespace gen {


class SourcesOp : public ak::UserOption {
public:
   using SourcesCt = std::vector< std::string >;

   static Option * create()
   {
      return new SourcesOp();
   }

   virtual string cmdline_id() {
      return "source-path,s";
   }

   virtual string name() {
      return "source-path";
   }

   virtual string description() {
      return "Sets source paths to iterate over. This option can be used multiple times";
   }

   virtual ParseOptionsBase::StorageType * storage_type() {
      return ParseOptionsBase::set_multiple< string >( &sources_paths_ );
   }

   virtual void execute() {
      LOG_CONSOLE("Great!! doing source-path stuff" )      
   }

   const SourcesCt & sources() const
   {
      return sources_paths_;
   }


private:
   SourcesCt sources_paths_;
};


} }


#endif

