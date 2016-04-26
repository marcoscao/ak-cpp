#ifndef AK_GENERATE_PROGRAM_OPTIONS__
#define AK_GENERATE_PROGRAM_OPTIONS__

#include "ak_core/ProgramOptionsBase.h"
#include <string>
#include <vector>


namespace ak {
namespace gen {

	class SourcesCmd;

   class ProgramOptions : public PO {
   public:

      ProgramOptions();

      void initialize();

      void process( int argc, char** argv );


   private:
      std::shared_ptr< SourcesCmd > sources_cmd_;

      void help_op_callback_();

      void version_op_callback_();

      void verbose_op_callback_();

	  void show_current_settings()_;

   };


} }

#endif

