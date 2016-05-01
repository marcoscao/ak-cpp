#include "ParseOptions.h"
#include "ak_core/AppManager.h"
#include "ak_core/Exception.h"
#include "ak_core/LogSystem.h"

#include "draft.h"

#include <iostream>

using namespace std;
using namespace ak;


int main(int argc, char** argv ) 
{
   LogSystem::get().initialize( "ak_generate.log", LogSystem::Level::Debug );

   LOG_I( "\n-------------------------------------------------------")
   LOG_I( "Starting ak_generate" );
      
   LOG_CONSOLE( "ak_generate\n" );

   try {

      AppManager app;

      app.set_options_parser( new gen::ParseOptions() );

      // Create desired options from factory registered ones
      app.add_options( { gen::ParseOptions::SOURCES_OP_ID, 
                         gen::ParseOptions::VERBOSE_OP_ID }, 
                         "Basic Options" );
      
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


   LOG_I( "Finished ak_generate" );
   LOG_I( "-------------------------------------------------------")

   LOG_CONSOLE( "Finished ok" );

   return 0;
}


