#include "ProgramOptions.h"
#include "SourcesCmd.h"
#include "ak_core/FileSystem.h"
#include "ak_core/Utils.h"

#include <iostream>

using namespace std;

namespace ak { namespace gen {

   ProgramOptions::ProgramOptions() 
   {
   }

   void ProgramOptions::initialize()
   {
      std::shared_ptr< SourcesCmd > src_p( new SourcesCmd() ); 
      
      // Basic and required  options
      add_group( "Basic Options", option_def_list { 
				
         option_def{ "help", "help command", nullptr, std::bind( &ProgramOptions::help_op_callback_, this ) },
         option_def{ "verbose,v", "sets verbose mode", nullptr, std::bind( &ProgramOptions::verbose_op_callback_, this ) },
        
         // sources managed by a customized command
         option_def{ "source-path,s", "sets the source paths to process files. Note that can be assigned multiple source paths", 
		  set_multiple< string >( &src_p->source_paths() ),
		  nullptr,
		  src_p }
         } 
      );

      // Extended and miscelanean options
      add_group( "Extended Options", option_def_list { 
            option_def{ "dry-run", "simulation. executes the command but with no side effects" },
            option_def{ "version", "current version", nullptr, std::bind( &ProgramOptions::version_op_callback_, this ) },
            }  
      );
   }

   void ProgramOptions::process( int argc, char** argv )
   {
      // let boost do the first processing stuff
      process_command_line_arguments( argc, argv );

      if( has_option( "dry-run" ) ) 
         LOG_I( "* 'dry-run' option found" ) 

      cout << endl << "Going to execute with this settings: " << endl;
      cout << " - sources : " << endl;
      cout << " - verbose : " << endl;
      cout << " - dry-run mode : " << endl;
      cout << endl;

      if( ak::util::prompt_question() == false ) {
         LOG_I( "Operation aborted by the user before start" )
         return;
      }
         

      // execute callback and command options in passed order
      execute_options( {"-v", "dry-run", "-s" } );
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

   void ProgramOptions::version_op_callback_()
   {
      cout << "Built April 2016" << endl; 
      cout << "version  2016.04.001" << endl;
   }

   void ProgramOptions::verbose_op_callback_()
   {
      cout << "verbose stuff here" << endl; 
   }


} } // end namespaces


