#include "SqlSystem.h"
#include <sqlite3.h>

namespace ak_core {

	SqlSystem::SqlSystem()
	: sqlite_( 0 )
	{
	}

	SqlSystem::SqlSystem()
	{
		if( sqlite_ )
			sqlite_->close();
	}

	bool SqlSystem::open_db( std::string const & db_name )
	{
		// TODO: open and check version to determine whether needed to be updated
		// maybe open an update_sql.def file and check if its version is greater than the internal db_version name
		if( sqlite_ ) {
			LOG_E( "databse ", db_name, "has been open previously" );
			return;
		}

		sqlite3_open( db_name.c_str(), &sqlite_ );
	}

	bool SqlSystem::create_db( std::string const & db_name, std::string const & sql_def_file = std::string() )
	{
	}

	bool SqlSystem::exist_db( std::string const & db_name ) const
	{
		/*
		 * Exists db file and is valid
		 */
	}

	bool SqlSystem::update_db( std::string const & db_name, std::string const & sql_def_file = std::string() )
	{
		// apply changes and updates db internal version to new one
	}

	bool SqlSystem::search_for_updates() const
	{
		// checking if update file exists
		// then request user to perform update
	}

	bool SqlSystem::execute_sql( std::string const & db_name ) const
	{
	}

	bool SqlSystem::exist_update_file_() const
	{
	}

}
