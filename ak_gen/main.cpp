#include "ParseOptions.h"
#include "HelpCmd.h"
#include "ak_core/AppManager.h"
#include "ak_core/Exception.h"
#include "ak_core/LogSystem.h"

#include <iostream>

using namespace std;
using namespace ak;


int main(int argc, char** argv ) 
{
   LogSystem::get().initialize( "_ak_gen.log", LogSystem::Level::Debug );

   LOG_I( "\n-------------------------------------------------------")
   LOG_I( "Starting ak_gen" );

   AppManager app;

   try {

      app.set_options_parser( new gen::ParseOptions() );

      // Create desired options from factory registered ones
      app.add_options( { gen::SOURCES_OP_ID, 
                         gen::HELP_OP_ID,
                         //gen::ParseOptions::MEDIA_OP_ID }, 
                         },
                         "Basic Options" );

      app.add_options( { gen::VERBOSE_OP_ID,  
                         gen::CHUNK_NUMBER_OP_ID, 
                         gen::VERSION_OP_ID, 
                         },
                         "Extended Options" );
      
      LOG_I( "Going to execute" );
      app.execute( argc, argv );

   }
   catch( ak::ak_options_exception const & e ) {
      LOG_E( "ak_options_exception", e.what() );
      cout << endl << e.what() << endl;
   }
   catch( ak::ak_exception const & e ) {
      LOG_E( "ak_exception", e.what() );
      cout << endl << e.what() << endl;
   }
   catch( std::exception const & e ) {
      LOG_E( "exception", e.what() );
      cout << endl << e.what() << endl;
   }

   LOG_I( "Finished ak_gen" );
   LOG_I( "-------------------------------------------------------")

   LOG_CONSOLE("");
   return 0;
}


