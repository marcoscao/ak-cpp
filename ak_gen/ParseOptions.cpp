#include "ParseOptions.h"
#include "CollectDataCmd.h"
#include "CurrentSettingsVisitor.h"
#include "HelpCmd.h"
#include "VersionCmd.h"

#include "ak_core/Factory.h"
#include "ak_core/FileSystem.h"
#include "ak_core/Utils.h"

#include <iostream>
#include <sstream>

using namespace std;

namespace ak { namespace gen {

   __AK_REGISTER_OPTION_CLASS__( HelpOp, HELP_OP_ID )
   __AK_REGISTER_OPTION_CLASS__( SourcesOp, SOURCES_OP_ID )
   __AK_REGISTER_OPTION_CLASS__( VerboseOp, VERBOSE_OP_ID )
   __AK_REGISTER_OPTION_CLASS__( VersionOp, VERSION_OP_ID )
   __AK_REGISTER_OPTION_CLASS__( MediaOp, MEDIA_OP_ID )
   __AK_REGISTER_OPTION_CLASS__( ChunkNumberOp, CHUNK_NUMBER_OP_ID )


   ParseOptions::ParseOptions() 
   {
   }

   // void ParseOptions::register_options( )
   // {
   //    // Factory<Option> & f = Factory<Option>::instance();
   //    //
   //    // f.register_item< SourcesOp >( SOURCES_OP_ID );  
   //    // f.register_item< HelpOp >( HELP_OP_ID );
   //    // f.register_item< VerboseOp >( VERBOSE_OP_ID );
   //    // f.register_item< VersionOp >( VERSION_OP_ID );
   //    // f.register_item< MediaOp >( MEDIA_OP_ID );
   //    // f.register_item< ChunkNumberOp >( CHUNK_NUMBER_OP_ID );
   //    // //f.register_item< MediaOp >( MEDIA_MODE_OP_ID );
   //    // //f.register_item< MediaOp >( MEDIA_FILES_OP_ID );
   // }

   void ParseOptions::execute() {

      // force to show always except when requesting only version
      // in such case show it and exit
      //execute_option_if( VERSION_OP_ID, true );

      if( has_user_entered_option( HELP_OP_ID ) ) {
         HelpCmd cmd;
         cmd.execute( *this );
         return;
      }

      if( has_user_entered_option( VERSION_OP_ID ) ) {
         VersionCmd cmd;
         cmd.execute(*this);
         return;
      }

      if( has_user_entered_option( SOURCES_OP_ID ) == false ) {
         LOG_CONSOLE("Please run with --help or -h to display correct usage and available options.");
         return;
      }

      
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

      CurrentSettingsVisitor cs( *this );
      apply_visitor( cs );

      LOG_CONSOLE( cs.current_settings().str() )
      cout << endl;
   }

} } // end namespaces


