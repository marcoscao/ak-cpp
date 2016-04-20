#include "ProgramOptions.h"
#include <iostream>

using namespace std;

namespace ak { 
namespace gen {

	ProgramOptions::ProgramOptions() 
  	: source_paths_() {

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
         	option_def{ "source_path,s", "sets the source path to process from. Note that can be assigned multiple source paths", 
				set_multiple_required< string >( &source_paths_ ),
				std::bind( &ProgramOptions::process_source_path_op_, this ) },
      		}
		);


      	// Extended and miscelanean options
		add_group( "Extended Options", option_def_list { 

         	option_def{ "dry-run", "simulation. executes the command but with no side effects" },

         	option_def{ "verbose,v", "optinally activate verbose mode" }
			}
		);
   }

   void ProgramOptions::process_no_callbacks()
   {
      if( has_option( "-v" ) ) 
         cout << "* 'verbose' option found" << endl;

      if( has_option( "dry-run" ) ) 
         cout << "* 'dry-run' option found" << endl;

   }

   void ProgramOptions::process_help_op_()
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

   void ProgramOptions::process_dry_run_op_()
   {
		cout << "!!! Doing in dry-run mode" << endl;
   }

   void ProgramOptions::process_source_path_op_() 
   {
         cout << "* doing source_path op. values: " << endl;
         for( auto i : source_paths_ ) {
            cout << "  - source_path : " << i << endl;
			traverse_source_path_( i );
			

		 }
   }

   void ProgramOptions::traverse_source_path_( std::string const & sp )
   {
	   FilesManager fm;
	
	   if( fm.is_folder( sp ) == false ) {
		log_debug( "Oops! Item " + sp " is not a folder" )
		return;
	   }

	   FilesManager::FileTypesContainer ct = fm.get_items( sp );
		for( auto i : ct ) {
			if( fm.is_file( i ) ) {
				log_debug( "Cool. " + i + " its a file" );
			}
			else if( fm.is_folder( i ) ) {
				log_debug( "Going down folder: " + i );
				traverse_source_path( i );
			}
			else {
				log_info( "Oops! I don't know wtf is " + i )
			}
		}
   }


} } // end namespaces



