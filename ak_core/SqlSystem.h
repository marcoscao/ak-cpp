#ifndef AK_CORE_SQL_SYSTEM_H__
#define AK_CORE_SQL_SYSTEM_H__

#include<string>

class sqlite3;

namespace ak_core {

	class SqlSystem {
	public:
		SqlSystem()

		~SqlSystem()

		// TODO: open and check version to determine whether needed to be updated
		// maybe open an update_sql.def file and check if its version is greater than the internal db_version name
		bool open_db( std::string const & db_name );

		bool create_db( std::string const & db_name, std::string const & sql_def_file = std::string() );

		/*
		 * Exists db file and is valid
		 */
		bool exist_db( std::string const & db_name ) const;

		bool update_db( std::string const & db_name, std::string const & sql_def_file = std::string() );

		/*
			 checking if update file exists
			 then request user to perform update
		 * 
		 */
		bool search_for_updates() const;

		bool execute_sql( std::string const & db_name ) const

	private:
		//shared_ptr< sqlite3 > sqlite_;
		sqlite3 * sqlite_;

		bool exist_update_file_() const;

	};

}

#endif
