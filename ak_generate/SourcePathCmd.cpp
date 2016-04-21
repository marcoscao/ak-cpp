#include "SourcePathCmd.h"
#include "ProgramOptions.h"
#include <iostream>

using namespace std;

namespace ak {
namespace gen {

   SourcePathCmd::SourcePathCmd( )
   {
   }

   void SourcePathCmd::execute( PO const & po )
   {
      cout << "Great! Executing SourcePath option command" << endl;

      for( auto i : source_paths_ ) {

         cout << "  - source_path : " << i << endl;
         traverse_source_path_( i );
      }
   }

   void SourcePathCmd::traverse_source_path_( std::string const & sp )
   {
      //FileSystem fm;
	
      // if( fm.is_folder( sp ) == false ) {
      //    cout <<  "Oops! Item " << sp << " is not a folder" << endl;
	//  return;
      // }
      //
      // FileSystem::FileTypesContainer ct = fm.get_items( sp );
      // for( auto i : ct ) {
      //
      //    if( fm.is_file( i ) ) {
	//     cout << "Cool. " << i << " its a file" << endl;
	//  }
	//  else if( fm.is_folder( i ) ) {
	//     cout << "Going down folder: " << i << endl;
	//     traverse_source_path( i );
	//  }
	//  else {
	//     cout << "Oops! I don't know wtf is " << i << endl;
	//  }
      // }
   }


} }

