#ifndef AK_CORE_FILESYSTEM_H__
#define AK_CORE_FILESYSTEM_H__

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

#include "LogSystem.h"
#include <string>
#include <vector>

namespace ak {

   class FileSystem {
   public:
      //!
      //! f_type is based on boost::filesystem path class
      //! 
      //!   .filename()    -> complete filename without path 
      //!   .stem()        -> name without extension
      //!   .type()        -> extension with the '.'
      //!   .parent_path() 
      //!   .root_path()
      //!   ...
      //!   
      using f_type = boost::filesystem::path;
      
      using DirContainer = std::vector< f_type >;


      // struct file_type_obj {
      //       
      //       std::string full_path_name;
      //       std::string name;
      //       std::string ext;
      //       std::string path_name;
      //       std::string parent_folder;
      //      
      //       // not sure to put these here
      //       long size;
      //       std::string date;
      //       int media;
      // };

      //! builds obj
      // file_type_obj generate_file_type_obj( std::string const & full_path_name );

      // sets working path
      // void set_working_path( std::string const & path );

      //long file_size( std::string const &, bool local = true );

      // long file_size( file_type_obj & );

      //long file_ext( file_type_obj & );

      std::string current_path() const
      {
         boost::filesystem::path cp( boost::filesystem::current_path() );
         // std::stringstream ss;
         // ss <<  cp;

         LOG_D( "current path:", cp );
         
         return cp.string();
      }

      bool exists( f_type const & full_path_name )
      {
         if( boost::filesystem::exists( full_path_name ) == false ) {
            LOG_D( "item :", full_path_name, "NOT Exists" );
            return false;
         }

         return true;
      }

      bool is_folder( f_type const & p )
      {
         if( !exists( p ) )
            return false;

         if( boost::filesystem::is_directory( p ) == false ) {
            LOG_T( "is folder :", p, "...", "NO" );
            return false;
         }
        
         LOG_T( "is folder :", p, "...", "YES" );
         return true;
      }

      bool is_file( f_type const & p )
      {
         if( !exists( p ) )
            return false;

         if( boost::filesystem::is_regular_file( p ) == false ) {
            LOG_T( "is_file :", p, "...", "NO" );
            return false;
         }
        
         LOG_T( "is_file :", p, "...", "YES" );
         return true;
      }

      /*
       * Returns container order by 2 groups
       *    - first group folders, ordered alphabetically
       *    - next group files, ordered alphabeticaly
       */
      DirContainer get_items( f_type const & p )
      {
         using namespace boost::filesystem;

         DirContainer v_folders;
         DirContainer v_files;

         std::copy_if( directory_iterator(p), directory_iterator(), std::back_inserter(v_folders), 
               [&v_files]( path const & i ){ 
                  if( is_directory( i ) ) 
                     return true;

                     v_files.push_back(i);
                  return false;
                  }
               );
         std::sort( begin(v_files), end(v_files) );
         std::sort( begin(v_folders), end(v_folders) );

         v_folders.insert( end(v_folders), begin(v_files), end(v_files) );
         return v_folders;
      }

      //! size in bytes
      long size( f_type const & p )
      {
         return boost::filesystem::file_size( p );
      }

   };

}

#endif

