#include "CollectDataCmd.h"
#include "ak_core/LogSystem.h"
#include "ParseOptions.h"
#include "SourcesOp.h"

using namespace std;

namespace ak { namespace gen {
   CollectDataCmd::CollectDataCmd()
   : using_verbose_( false )
   {
   }

   Command * CollectDataCmd::create()
   {
      return new CollectDataCmd();
   }

   string CollectDataCmd::name() {
      return "Collect Data Command";
   }

   void CollectDataCmd::execute( ParseOptionsBase const & pob ) {
      //LOG_CONSOLE("Great!! doing source-path stuff" )      
      LOG_I( "Executing Collect Data Command" )
   
      if( pob.has_user_entered_option( ParseOptions::VERBOSE_OP_ID ) )
         using_verbose_ = true;

      SourcesOp::SourcesCt const & ct = static_cast<SourcesOp*>( pob.option_ptr( ParseOptions::SOURCES_OP_ID ) )->sources();
      for( auto i : ct ) {

         LOG_I( "Iterating over source path", i );
         LOG_CONSOLE( "\nIterating over source path", i + "..." );
         
         stats st = traverse_source_path_( i );
         traverse_source_path_( i );
         
         LOG_I( "Source Path", i, "has", st.files, "files and ", st.folders, "folders which occupies", ak::util::to_mb( st.size), "Mb" );
         LOG_CONSOLE( "  Source Path", i, "has", st.files, "files and ", st.folders, "folders which occupies", ak::util::to_mb( st.size), "Mb" );
      }
   }

   CollectDataCmd::stats CollectDataCmd::traverse_source_path_( FileSystem::f_type const & sp )
   {
       FileSystem fs;
       stats st;
   
      if( fs.is_folder( sp ) == false ) {
         LOG_CONSOLE( "Source path:", sp, "is not a directory");
         LOG_I( "Source path:", sp, "is not a directory");
         return st;
      }

      LOG_D( "traversing path:",sp );
       
      if( using_verbose_ ) 
         LOG_CONSOLE( "  - Processing folder:", sp, "..." );
   
      FileSystem::DirContainer ct = fs.get_items( sp );
   
      for( FileSystem::f_type & i : ct ) {
         LOG_T( "traverse_source_path found item: ", i );
   
         // if( i.filename() == "." ) {
         //    LOG_CONSOLE( "Omitting '", sp, "' path");
         //    LOG_I( "Omitting '", sp, "' path");
         //    return st;
         // }
      
         if( fs.is_file( i ) ) {
            LOG_I( "found file:", i.filename(), "type", i.extension(), "size", fs.size( i ) );

            if( using_verbose_ )
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
       
      if( using_verbose_ )
         LOG_CONSOLE( "   Folder", sp.filename(), "has", st.files, "files and ", st.folders, "folders and occupies", ak::util::to_mb( st.size), "Mb" );
   
      return st;
   }

} }



