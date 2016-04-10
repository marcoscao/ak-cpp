#include "ak_core/ProgramOptionsBase.h"
#include <iostream>

using namespace std;
using namespace ak;

int main(int argc, char** argv )
{
   cout << "Testing program_options..." << endl;

   PO po;
   PO::option_def_list l;
   l.push_back( PO::option_def{ "help,h", "help command" });
   
   po.add_options( l );

}

