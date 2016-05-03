#ifndef AK_GEN_COLLECT_DATA_COMMAND_H__
#define AK_GEN_COLLECT_DATA_COMMAND_H__

#include "ak_core/FileSystem.h"
#include "ak_core/Command.h"
#include "ak_core/ParseOptionsBase.h"

#include <iostream>
#include <string>

namespace ak { namespace gen {

   class CollectDataCmd : public ak::Command {
   public:

      struct stats {
         long files;
         long folders;
         unsigned long size;

         stats() : files(0), folders(0), size(0) {}

         stats operator+( stats const & b )
         {
            files += b.files;
            folders += b.folders;
            size += b.size;

            return *this;
         }
      };


      CollectDataCmd();

      static Command * create();

      virtual std::string name();

      virtual void execute( ParseOptionsBase const & );

      //virtual void accept( VisitorCmd & );

   private:
      bool using_verbose_;

      stats traverse_source_path_( FileSystem::f_type const & source_path );
   };


} }


#endif

