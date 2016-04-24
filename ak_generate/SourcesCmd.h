#ifndef AK_GENERATE_SOURCE_PATH_COMMAND_H__
#define AK_GENERATE_SOURCE_PATH_COMMAND_H__

#include "ak_core/Command.h"
#include "ak_core/FileSystem.h"
#include "ak_core/ProgramOptionsBase.h"
#include <vector>

namespace ak {
namespace gen {

   class SourcesCmd : public Command {
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

      
      //! Holds passed source paths through command line
      using StrContainer = std::vector< std::string >;

      SourcesCmd( );
		
      virtual void execute( PO const & );

      StrContainer & source_paths()
      {
         return source_paths_;
      }

   private:
      StrContainer source_paths_;


      SourcesCmd::stats traverse_source_path_( FileSystem::f_type const & sp );

   };

} }

#endif

