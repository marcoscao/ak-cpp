#ifndef AK_CORE_FILESMANAGER_H__
#define AK_CORE_FILESMANAGER_H__

namespace ak {

	class FilesManager {
	public:


		struct file_type_obj {
			
			std::string full_path_name;
			std::string name;
			std::string ext;
			std::string path_name;
			std::string parent_folder;
			
			long size;
			std::string date;
			int media;
		};

		//! builds obj
		file_type_obj generate_file_type_obj( std::string const & full_path_name );
		
		// sets working path
		void set_working_path( std::string const & path );

		//long file_size( std::string const &, bool local = true );

		long file_size( file_type_obj & );

		//long file_ext( file_type_obj & );


	};

}

#endif

