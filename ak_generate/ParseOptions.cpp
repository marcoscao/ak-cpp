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
      f.register_item< SourcesOp >( SOURCES_OP_ID );  
      f.register_item< HelpOp >( HELP_OP_ID );
      f.register_item< VerboseOp >( VERBOSE_OP_ID );
      f.register_item< VersionOp >( VERSION_OP_ID );
      //f.register_item< VersionOp >( DRY_RUN_OP_ID );
   }

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


