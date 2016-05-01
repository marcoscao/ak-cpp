#ifndef AK_DRAFT_H__
#define AK_DRAFT_H__

#include "ak_core/Exception.h"
#include "ak_core/Factory.h"
#include "ak_core/Option.h"
#include "ak_core/ParseOptionsBase.h"

#include <iostream>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

using namespace std;

namespace ak {


// class SourcesOp : public UserOption {
// public:
//    using SourcesCt = std::vector< std::string >;
//
//    static Option * create()
//    {
//       return new SourcesOp();
//    }
//
//    virtual string cmdline_id() {
//       return "source-path,s";
//    }
//
//    virtual string name() {
//       return "source-path";
//    }
//
//    virtual string description() {
//       return "Sets source paths to iterate over. This option can be used multiple times";
//    }
//
//    virtual ParseOptionsBase::StorageType * storage_type() {
//       return ParseOptionsBase::set_multiple< string >( &sources_paths_ );
//    }
//
//    virtual void execute() {
//       LOG_CONSOLE("Great!! doing source-path stuff" )      
//    }
//
//    const SourcesCt & sources() const
//    {
//       return sources_paths_;
//    }
//
//
// private:
//    SourcesCt sources_paths_;
// };
//



   class HelpOp : public UserOption {
   public:
      static int ID;

      virtual string cmdline_id() {
         return "help,h";
      }

      virtual string name() {
         return "help";
      }

      static Option * create()
      {
         return new HelpOp();
      }

      // virtual Option::option_def definition()
      // {
      //    return { "sources", "sources", "s", "Sets source paths to iterate over" };
      // }

   };

class VerboseOp : public UserOption {
public:

   static Option * create()
   {
      return new VerboseOp();
   }

   virtual string cmdline_id() {
      return "verbose";
   }

   virtual string name() {
      return "verbose";
   }

   virtual string description() {
      return "Verbose mode";
   }

   virtual void execute() {
      LOG_CONSOLE("Great!! doing verbose stuff" )      
   }
};



}



#endif


