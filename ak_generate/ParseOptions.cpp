#include "ParseOptions.h"
#include "HelpOp.h"
#include "SourcesOp.h"
#include "VerboseOp.h"
#include "VersionOp.h"

#include "ak_core/Factory.h"
#include "ak_core/FileSystem.h"
#include "ak_core/Utils.h"

#include <iostream>
#include <sstream>

using namespace std;

namespace ak { namespace gen {

   ParseOptions::ParseOptions() 
   {
   }

   void ParseOptions::register_options( factory<Option> & f )
   {
      f.register_item( SOURCES_OP_ID, SourcesOp::create );  
      f.register_item( HELP_OP_ID, HelpOp::create );
      f.register_item( VERBOSE_OP_ID, VerboseOp::create );
      f.register_item( VERSION_OP_ID, VersionOp::create );
   }

   // void ProgramOptions::initialize()
   // {
   //    //std::shared_ptr< SourcesCmd > src_p( new SourcesCmd() ); 
   //    
   //    // Basic and required  options
   //    add_group( "Basic Options", option_def_list { 
	// 			
   //       option_def{ "help", "help command", nullptr, std::bind( &ProgramOptions::help_op_callback_, this ) },
   //       option_def{ "verbose,v", "sets verbose mode", nullptr, std::bind( &ProgramOptions::verbose_op_callback_, this ) },
   //      
   //       // sources managed by a customized command
   //       option_def{ "source-path,s", "sets the source paths to process files. Note that can be assigned multiple source paths", 
	// 	  set_multiple< string >( &sources_cmd_->source_paths() ),
	// 	  nullptr,
	// 	  sources_cmd_ }
   //       } 
   //    );
   //
   //    // Extended and miscelanean options
   //    add_group( "Extended Options", option_def_list { 
   //          option_def{ "dry-run", "simulation. executes the command but with no side effects" },
   //          option_def{ "version", "current version", nullptr, std::bind( &ProgramOptions::version_op_callback_, this ) },
   //          }  
   //    );
   // }

   // void ProgramOptions::process( int argc, char** argv )
   // {
   //    // let boost do the first processing stuff
   //   /process_command_line_arguments( argc, argv );
   //
   //    show_current_settings_();
   //
   //    if( ak::util::prompt_question() == false ) {
   //       LOG_I( "Operation aborted by the user before start" )
   //       return;
   //    }
   //
   //    // execute callback and command options in order
   //    if( has_option("verbose") )
   //       execute_options( { "-v" } );
   //    
   //    execute_options( { "dry-run", "-s" } );
   // }

   void ParseOptions::execute() {

      // force to show always except when requesting only version
      // in such case show it and exit
      execute_option_if( VERSION_OP_ID, true );

      if( has_user_entered_option( VERSION_OP_ID ) )
         return;

      if( no_user_options() ) {
         LOG_CONSOLE("Please run with --help or -h to display correct usage and available options.");
         return;
      }

      if( execute_option_if( HELP_OP_ID ) )
         return;
      
      show_current_settings_();

      if( ak::util::prompt_question() == false ) {
         LOG_I( "Operation aborted by the user before start" )
         return;
      }

      execute_option_if( SOURCES_OP_ID );
   }

   // void ProgramOptions::help_op_callback_()
   // {
   //    cout << "ak_generate " << endl;
   //    version_op_callback_();
   //
   //    cout << endl << endl;
   //    cout << "   usage  ak_generate -source_path [ --source_path ... ]"; 
   //    cout << endl << endl;
   //    cout << "   # example 1: Copyng from different sources" << endl;
   //    cout << "   ak_generate -s /Vol/media/a -s /Vol/media/d" << endl;
   //    cout << endl << endl;
   //
   //    print_usage( "" );
   // }
   //
   // void ProgramOptions::version_op_callback_()
   // {
   //    cout << "Built April 2016" << endl; 
   //    cout << "version  2016.04.001" << endl;
   // }
   //
   // void ProgramOptions::verbose_op_callback_()
   // {
   //    cout << "verbose stuff here" << endl; 
   // }
   //
   void ParseOptions::show_current_settings_()
   {
      cout << endl;
      LOG_CONSOLE( "Going to execute with the following options\n" )

      //if( has_entered_option("dry-run") )
      //   LOG_CONSOLE( " - dry-run mode :", "YES" )
	 
      if( has_user_entered_option( SOURCES_OP_ID ) ) {
         
         SourcesOp * op = static_cast<SourcesOp*>( option_ptr( SOURCES_OP_ID ) );

          stringstream ss;
          auto const & v = op->sources();
          auto it = begin(v);
          do {
             ss << "\"" << *it << "\"";
      
            if( ++it != end(v) )
              ss << endl << "                 ";
     
          } while( it != end(v) );
      
          LOG_CONSOLE( " -", op->name(), ":", ss.str() )
      }

      
      if( has_user_entered_option( VERBOSE_OP_ID ) )
         LOG_CONSOLE( " - verbose :", "YES" )
      else
         LOG_CONSOLE( " - verbose :", "NO" )

      cout << endl;
   }

} } // end namespaces


