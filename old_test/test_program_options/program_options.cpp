#include "ak_core/ProgramOptionsBase.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace ak;

int main(int argc, char** argv )
{
	cout << "Testing program_options..." << endl;


	PO po;

	PO::option_def_list l{ 
		PO::option_def{ "help", "help command", nullptr },
		
		 PO::option_def{ "verbose,v", "doing the operation verbose"},
		 PO::option_def{ "source,s", "source" },
		 PO::option_def{ "target,t", "target" },
		 PO::option_def{ "dry_run", "dry run" }
		 //PO::option_def{ "world,w", "set world name", po::value<std::vector<std::string>>()( &world ) }
      //     //  "words for the sentence, specify multiple times" }
      // //       (",t", "just a temp option that does very little")
      // //       ("necessary,n", po::value<std::string>()->required(), "necessary!")
      // //       ("manual,m", po::value<std::string>(), "extract value manually")
      // //       ("add", po::value<int>(&add)->required(), "additional options")
      // //       ("like", po::value<int>(&like)->required(), "this");
	};

	po.add_group( "Config Options", l );


	// PO::option_def_list l2{ 
	// 	PO::option_def{ "xhelp", "help command" },
	// 	PO::option_def{ "xverbose,m", "doing the operation verbose"},
	// 	PO::option_def{ "xsource", "source" },
	// 	PO::option_def{ "xtarget,p", "target" },
	// 	PO::option_def{ "xdry_run", "dry run" }
	// };
    //
	// po.add_group( "Extra Options", l2 );

	po.process_command_line( argc, argv );

	if( po.has_option( "help" ) || po.no_user_option() ) 
		po.print_usage("testing_program_options");

	if( po.has_option( "verbose" ) ) {
		cout << "........" << endl;
		cout << "... doing verbose....." << endl;
		cout << "........" << endl;
	}

		
}

