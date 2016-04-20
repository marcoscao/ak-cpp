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

   		void process_no_callbacks();


	private:
   		StrContainer source_paths_;

   
   		void process_help_op_();

   		void process_dry_run_op_();

   		void process_source_path_op_();

	};

}
}

#endif

