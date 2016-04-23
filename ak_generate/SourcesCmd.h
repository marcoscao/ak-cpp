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


      void traverse_source_path_( FileSystem::f_type const & sp );

   };

} }

#endif

