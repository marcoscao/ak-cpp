#include "FileSystem.h"
#include <string>

using namespace std;

namespace ak {
		
   FileSystem::file_type_obj FileSystem::generate_file_type_obj( string const & full_path_name )
   {
      file_type_obj f;

      f.full_path_name = full_path_name;
                  // std::string full_path_name;
                  // std::string name;
                  // std::string ext;
                  // std::string path_name;
                  // std::string parent_folder;
                  //
                  // long size;
                  // std::string date;
                  // int media;

      return f;   
   }

   void FileSystem::set_working_path( string const & path ) 
   {
      //! TODO
   }

   long FileSystem::file_size( file_type_obj & f )
   {
      //! TODO
      return -1;
   }

}

