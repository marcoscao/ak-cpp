#include "SourcesCmd.h"
#include "ProgramOptions.h"

#include <iostream>

using namespace std;

namespace ak {
namespace gen {

   SourcesCmd::SourcesCmd( )
   {
   }

   void SourcesCmd::execute( PO const & po )
   {
      FileSystem fs;

      for( auto i : source_paths_ ) {

         LOG_D( "Executing Sources Command. Iterating over path", i );
         traverse_source_path_( i );
      }
   }

   void SourcesCmd::traverse_source_path_( FileSystem::f_type const & sp )
   {
      FileSystem fm;
	
      if( fm.is_folder( sp ) == false ) {
          LOG_D( "source path:", sp, "is not a directory");
	  return;
      }
     
      LOG_D( "traversing path:",sp );

      FileSystem::DirContainer ct = fm.get_items( sp );


      unsigned long folder_size = 0;
      int total_files = 0;
      int total_folders = 0;

      for( FileSystem::f_type & i : ct ) {
         //LOG_T( "traverse_source_path found item: ", i );

         if( fm.is_file( i ) ) {
            LOG_I( "found file:", i.filename(), "type", i.extension(), "size", fm.size( i ) );
            folder_size += fm.size(i);
            ++total_files;
         }

         if( fm.is_folder( i ) ) {
            LOG_T("traverse going down folder: ", i);
            traverse_source_path_( i );
            ++total_folders;
         }

      }

      LOG_I( "total files: ", total_files );
      LOG_I( "total folders: ", total_folders );
      LOG_I( "total folder size: ", to_mb( folder_size ), "Mb" );

   }


} }

