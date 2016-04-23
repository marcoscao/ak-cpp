#include "ProgramOptions.h"
#include "ak_core/Exception.h"
#include "ak_core/LogSystem.h"

#include <iostream>

using namespace std;
using namespace ak;
using namespace ak::gen;


int main(int argc, char** argv ) 
{
   LogSystem::get().initialize( "ak_generate.log", LogSystem::Level::Debug );

   LOG_I( "Starting ak_generate" );
   
   int j = 98;
   LOG_D( "esto", "es", "j=", j )


   ProgramOptions po;

   try {
      
      // Sets the options groups
      po.initialize();

      // This iterate over available options calling those with callbacks
      po.execute( argc, argv );

      // process all those options we do not register with callbacks
      po.process_manually();

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

}


