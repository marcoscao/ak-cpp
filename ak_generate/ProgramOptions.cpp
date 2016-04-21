#include "ProgramOptions.h"
#include "SourcePathCmd.h"
#include "ak_core/FileSystem.h"

#include <iostream>

using namespace std;

namespace ak { 
namespace gen {

   ProgramOptions::ProgramOptions() 
   : source_paths_() 
   {

   }

   void ProgramOptions::initialize()
   {
      // Basic and required  options
      add_group( "Basic Options", option_def_list { 
				
         // no callback assigned
         option_def{ "help", "help command", 
		  nullptr,
		  std::bind( &ProgramOptions::process_help_op_, this ) },
        
         // multiple managed by the user
         option_def{ "source-path,s", "sets the source paths to process files. Note that can be assigned multiple source paths", 
		  set_multiple< string >( &source_paths_ ),
		  std::bind( &ProgramOptions::process_source_path_op_, this ) },
		  new SourcePathCommand()
          } 
      );

      // Extended and miscelanean options
      add_group( "Extended Options", option_def_list { 
            option_def{ "dry-run", "simulation. executes the command but with no side effects" },
            option_def{ "verbose,v", "optinally activate verbose mode" }
            }  
      );
   }

   void ProgramOptions::process_options_manually()
   {
      if( has_option( "-v" ) ) 
         cout << "* 'verbose' option found" << endl;

      if( has_option( "dry-run" ) ) 
         cout << "* 'dry-run' option found" << endl;

   }

   void ProgramOptions::help_op_callback_()
   {
      cout << "ak_generate " << endl;
      cout << "version 2016.1.01";
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

   void ProgramOptions::source_path_op_callback_() 
   {
      cout << "* doing source_path op. values: " << endl;

      for( auto i : source_paths_ ) {

         cout << "  - source_path : " << i << endl;
         traverse_source_path_( i );
      }

   }

   // void ProgramOptions::traverse_source_path_( std::string const & sp )
   // {
   //    FileSystem fm;
	//
   //    // if( fm.is_folder( sp ) == false ) {
   //    //    cout <<  "Oops! Item " << sp << " is not a folder" << endl;
	// //  return;
   //    // }
   //    //
   //    // FileSystem::FileTypesContainer ct = fm.get_items( sp );
   //    // for( auto i : ct ) {
   //    //
   //    //    if( fm.is_file( i ) ) {
	// //     cout << "Cool. " << i << " its a file" << endl;
	// //  }
	// //  else if( fm.is_folder( i ) ) {
	// //     cout << "Going down folder: " << i << endl;
	// //     traverse_source_path( i );
	// //  }
	// //  else {
	// //     cout << "Oops! I don't know wtf is " << i << endl;
	// //  }
   //    // }
   // }
   //

} } // end namespaces



