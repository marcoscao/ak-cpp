#ifndef AK_GENERATE_SOURCE_PATH_COMMAND_H__
#define AK_GENERATE_SOURCE_PATH_COMMAND_H__

#include "ak_core/Command.h"
#include "ak_core/ProgramOptionsBase.h"
#include <vector>

namespace ak {
namespace gen {

   class SourcePathCmd : public Command {
   public:
      using StrContainer = std::vector< std::string >;

      SourcePathCmd( );
		
      virtual void execute( PO const & );

   private:
      StrContainer source_paths_;
      
      void traverse_source_path_( std::string const & sp );

   };

} }

#endif

