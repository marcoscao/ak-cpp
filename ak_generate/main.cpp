#include "ProgramOptions.h"
#include <iostream>

using namespace std;
using namespace ak::gen;


int main(int argc, char** argv ) {

   ProgramOptions po;

   // Sets the options groups
   po.initialize();

   // This iterate over available options calling those with callbacks
   po.execute( argc, argv );

   // process all those options we do not register with callbacks
   po.process_no_callbacks();
}

