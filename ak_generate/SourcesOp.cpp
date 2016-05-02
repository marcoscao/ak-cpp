#include "SourcesOp.h"
#include "ParseOptions.h"

using namespace std;

namespace ak { namespace gen {
   SourcesOp::SourcesOp()
   : using_verbose_( false ),
     sources_paths_()
   {
   }

   Option * SourcesOp::create()
   {
      return new SourcesOp();
   }

   string SourcesOp::cmdline_id() {
      return "source-path,s";
   }

   string SourcesOp::name() {
      return "source-path";
   }

   string SourcesOp::description() {
      return "Sets source paths to iterate over. This option can be used multiple times";
   }

   ParseOptionsBase::StorageType * SourcesOp::storage_type() {
      return ParseOptionsBase::set_multiple< string >( &sources_paths_ );
   }

   void SourcesOp::execute( ParseOptionsBase const & pob ) {
      //LOG_CONSOLE("Great!! doing source-path stuff" )      
      LOG_I( "Executing Sources Command" )
   
      if( pob.has_user_entered_option( ParseOptions::VERBOSE_OP_ID ) )
         using_verbose_ = true;

      for( auto i : sources_paths_ ) {

         LOG_I( "Iterating over source path", i );
         LOG_CONSOLE( "\nIterating over source path", i + "..." );
         
         stats st = traverse_source_path_( i );
         traverse_source_path_( i );
         
         LOG_I( "Source Path", i, "has", st.files, "files and ", st.folders, "folders which occupies", ak::util::to_mb( st.size), "Mb" );
         LOG_CONSOLE( "  Source Path", i, "has", st.files, "files and ", st.folders, "folders which occupies", ak::util::to_mb( st.size), "Mb" );
      }
   }

   const SourcesOp::SourcesCt & SourcesOp::sources() const
   {
      return sources_paths_;
   }

   SourcesOp::stats SourcesOp::traverse_source_path_( FileSystem::f_type const & sp )
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



