#include "ProgramOptions.h"
#include "ak_core/Exception.h"

#include <iostream>

using namespace std;
using namespace ak::gen;


int main(int argc, char** argv ) {

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
      cout << endl << e.what() << endl;
   }
   catch( ak::ak_exception const & e ) {
      cout << endl << e.what() << endl;
   }
   catch( std::exception const & e ) {
      cout << endl << e.what() << endl;
   }

}

