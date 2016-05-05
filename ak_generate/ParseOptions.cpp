#include "ParseOptions.h"
#include "ChunkOp.h"
#include "CollectDataCmd.h"
#include "HelpOp.h"
#include "MediaOp.h"
//#include "SourcesOp.h"
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
      f.register_item< SourcesOp >( SourcesOp::ID ); //SOURCES_OP_ID );  
      f.register_item< HelpOp >( HELP_OP_ID );
      f.register_item< VerboseOp >( VERBOSE_OP_ID );
      f.register_item< VersionOp >( VERSION_OP_ID );
      //f.register_item< VersionOp >( DRY_RUN_OP_ID );
      f.register_item< MediaOp >( MEDIA_OP_ID );
      f.register_item< ChunkOp >( CHUNK_SIZE_OP_ID );
      //f.register_item< MediaOp >( MEDIA_MODE_OP_ID );
      //f.register_item< MediaOp >( MEDIA_FILES_OP_ID );
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

      //execute_option_if( SOURCES_OP_ID );
      CollectDataCmd cd_cmd;
      cd_cmd.execute( *this );
   }

   void ParseOptions::show_current_settings_()
   {
      cout << endl;
      LOG_CONSOLE( "Going to execute with the following options\n" )

      //if( has_entered_option("dry-run") )
      //   LOG_CONSOLE( " - dry-run mode :", "YES" )
	 
      if( has_user_entered_option( SOURCES_OP_ID ) ) {
         
         SourcesOp * op = static_cast<SourcesOp*>( option_ptr( SOURCES_OP_ID ) );

          stringstream ss;
          auto const & v = op->get_data(); //op->sources();
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

      //if( has_user_entered_option( MEDIA_OP_ID ) ) {
         MediaOp * op = static_cast<MediaOp*>( option_ptr( MEDIA_OP_ID ) );
         LOG_CONSOLE( " - media :", op->media() )
      //}
      //else
      //  LOG_CONSOLE( " - media :", "default" )

      cout << endl;
   }

} } // end namespaces


