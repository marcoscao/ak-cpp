#include "ParseOptions.h"
#include "GenOptions.h"
#include "CollectDataCmd.h"
#include "CurrentSettingsVisitor.h"
#include "HelpCmd.h"
#include "VersionCmd.h"

//#include "ak_core/Factory.h"
//#include "ak_core/FileSystem.h"
#include "ak_core/Utils.h"

#include <iostream>
#include <sstream>

using namespace std;



namespace ak { namespace gen {

   // AK_DEFINE_OPTION_WITH_MULTIPLE_VALUES( 
   //    SourcesOp, SOURCES_OP_ID, 
   //    "source-path,s", "source-path",
   //    "Sets source paths to iterate over. This option can be used multiple times", 
   //    std::string )
   //
   // AK_DEFINE_OPTION( 
   //    HelpOp, HELP_OP_ID, 
   //    "help,h", "help", 
   //    "Shows usage Help and available options" )
   //
   // AK_DEFINE_OPTION( 
   //    VerboseOp, VERBOSE_OP_ID, 
   //    "verbose", "verbose", 
   //    "Activate Verbose mode" ) 
   //
   // AK_DEFINE_OPTION( 
   //    VersionOp, VERSION_OP_ID, 
   //    "version,v", "version", 
   //    "Show current version info" ) 
   //
   // AK_DEFINE_OPTION_WITH_UNIQUE_VALUE( 
   //    MediaOp, MEDIA_OP_ID, 
   //    "media", "media", 
   //    "Media to search for", 
   //    std::string, "audio" ) 
   //
   // AK_DEFINE_OPTION_WITH_UNIQUE_VALUE( 
   //    ChunkNumberOp, CHUNK_NUMBER_OP_ID, 
   //    "chunk-number", "chunk number", 
   //    "Number of chunk files to process in a group. Default is 50", 
   //    int, 50 ) 
   //
   //
   //
   // __AK_REGISTER_OPTION_CLASS__( HelpOp, HELP_OP_ID )
   // __AK_REGISTER_OPTION_CLASS__( SourcesOp, SOURCES_OP_ID )
   // __AK_REGISTER_OPTION_CLASS__( VerboseOp, VERBOSE_OP_ID )
   // __AK_REGISTER_OPTION_CLASS__( VersionOp, VERSION_OP_ID )
   // __AK_REGISTER_OPTION_CLASS__( MediaOp, MEDIA_OP_ID )
   // __AK_REGISTER_OPTION_CLASS__( ChunkNumberOp, CHUNK_NUMBER_OP_ID )


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

      if( has_user_entered_option( HelpOp::ID ) ) { //HELP_OP_ID ) ) {
         HelpCmd cmd;
         cmd.execute( *this );
         return;
      }

      if( has_user_entered_option( VERSION_OP_ID ) ) {
         VersionCmd cmd;
         cmd.execute(*this);
         return;
      }

      if( has_user_entered_option( SourcesOp::ID ) == false ) {
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


