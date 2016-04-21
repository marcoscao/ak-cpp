#ifndef AK_GENERATE_PROGRAM_OPTIONS__
#define AK_GENERATE_PROGRAM_OPTIONS__

#include "ak_core/ProgramOptionsBase.h"
#include <string>
#include <vector>


namespace ak {
namespace gen {

   class ProgramOptions : public PO {
   public:
		
      using StrContainer = std::vector< std::string >;

      ProgramOptions();

      void initialize();

      void process_manually();


   private:
      StrContainer source_paths_;

      void help_op_callback_();

      void dry_run_op_callback_();

      void source_path_op_callback_();

      void traverse_source_path_( std::string const & sp );

   };


} }

#endif

