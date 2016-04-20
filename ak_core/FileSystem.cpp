#include "FileSystem.h"

namespace ak {
		

	file_type_obj FilesManager::generate_file_type_obj( std::string const & full_path_name )
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
	}

	void FilesManager::set_working_path( std::string const & path ) 
	{
	}

	long FilesManager::file_size( file_type_obj & )
	{
	}

}

