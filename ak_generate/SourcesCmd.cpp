#include "SourcesCmd.h"
#include "ProgramOptions.h"

#include <iostream>

using namespace std;

namespace ak {
namespace gen {


   SourcesCmd::SourcesCmd( )
   : verbose_( false ) {
   }

   void SourcesCmd::execute( PO const & po )
   {
      LOG_I( "Executing Sources Command" )
   
      if( po.has_option( "verbose" ) )
         verbose_ = true;

      for( auto i : source_paths_ ) {

         LOG_I( "Iterating over source path", i );
         LOG_CONSOLE( "\nIterating over source path", i + "..." );
         stats st = traverse_source_path_( i );
         
         LOG_I( "Source Path", i, "has", st.files, "files and ", st.folders, "folders which occupies", ak::util::to_mb( st.size), "Mb" );
         LOG_CONSOLE( "  Source Path", i, "has", st.files, "files and ", st.folders, "folders which occupies", ak::util::to_mb( st.size), "Mb" );
      }
   }

   SourcesCmd::stats SourcesCmd::traverse_source_path_( FileSystem::f_type const & sp )
   {
      FileSystem fs;
      stats st;

      if( fs.is_folder( sp ) == false ) {
          LOG_D( "source path:", sp, "is not a directory");
	  return st;
      }
     
      LOG_D( "traversing path:",sp );
      
      if( verbose_ ) 
         LOG_CONSOLE( "  - Processing folder:", sp, "..." );

      FileSystem::DirContainer ct = fs.get_items( sp );

      for( FileSystem::f_type & i : ct ) {
         //LOG_T( "traverse_source_path found item: ", i );

         if( fs.is_file( i ) ) {
            LOG_I( "found file:", i.filename(), "type", i.extension(), "size", fs.size( i ) );
            
            if( verbose_ )
               LOG_CONSOLE( "    - found file:", i.filename(), "type", i.extension(), "size", fs.size( i ) );
            
            st.size += fs.size(i);
            st.files++;
         }

         if( fs.is_folder( i ) ) {
            LOG_T("traverse going down folder: ", i);
            
            st.folders++;

            stats st_child = traverse_source_path_( i );
            
            st=st + st_child;
         }
      }

      LOG_I( "Folder", sp.filename(), "has", st.files, "files and ", st.folders, "folders and occupies", ak::util::to_mb( st.size), "Mb" );
      
      if( verbose_ )
         LOG_CONSOLE( "   Folder", sp.filename(), "has", st.files, "files and ", st.folders, "folders and occupies", ak::util::to_mb( st.size), "Mb" );

      return st;
   }


} }

