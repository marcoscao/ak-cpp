#include "ProgramOptions.h"
#include "SourcesCmd.h"
#include "ak_core/FileSystem.h"

#include <iostream>

using namespace std;

namespace ak { 
namespace gen {

   ProgramOptions::ProgramOptions() 
   {

   }

   void ProgramOptions::initialize()
   {
      std::shared_ptr< SourcesCmd > src_p( new SourcesCmd() ); 
      
      // Basic and required  options
      add_group( "Basic Options", option_def_list { 
				
         option_def{ "help", "help command", 
		  nullptr,
		  std::bind( &ProgramOptions::help_op_callback_, this ) },

         option_def{ "version", "current version", 
		  nullptr,
		  std::bind( &ProgramOptions::version_op_callback_, this ) },
        
         // multiple managed by the user
         option_def{ "source-path,s", "sets the source paths to process files. Note that can be assigned multiple source paths", 
		  set_multiple< string >( &src_p->source_paths() ),
		  nullptr,
		  src_p }
          } 
      );

      // Extended and miscelanean options
      add_group( "Extended Options", option_def_list { 
            option_def{ "dry-run", "simulation. executes the command but with no side effects" },
            option_def{ "verbose,v", "optinally activate verbose mode" }
            }  
      );
   }

   void ProgramOptions::process_manually()
   {
      if( has_option( "-v" ) ) 
         cout << "* 'verbose' option found" << endl;

      if( has_option( "dry-run" ) ) 
         cout << "* 'dry-run' option found" << endl;

   }

   void ProgramOptions::help_op_callback_()
   {
      cout << "ak_generate " << endl;
      version_op_callback_();

      cout << endl << endl;
      cout << "   usage  ak_generate -source_path [ --source_path ... ]"; 
      cout << endl << endl;
      cout << "   # example 1: Copyng from different sources" << endl;
      cout << "   ak_generate -s /Vol/media/a -s /Vol/media/d" << endl;
      cout << endl << endl;

      print_usage( "" );
   }

   void ProgramOptions::dry_run_op_callback_()
   {
      cout << "!!! Doing in dry-run mode" << endl;
   }

   void ProgramOptions::version_op_callback_()
   {
      cout << "Built April 2016" << endl; 
      cout << "version  2016.04.001" << endl;
   }


} } // end namespaces



