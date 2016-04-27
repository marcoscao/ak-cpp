#include "SqlSystem.h"
#include "LogSystem.h"

#include <sqlite3.h>

namespace ak {

   SqlSystem::SqlSystem()
   : sqlite_( 0 )
   {
   }

   SqlSystem::~SqlSystem()
   {
      if( sqlite_ )
         sqlite3_close( sqlite_ );
   }

   bool SqlSystem::open_db( std::string const & db_name )
   {
      // TODO: open and check version to determine whether needed to be updated
      // maybe open an update_sql.def file and check if its version is greater than the internal db_version name
      if( sqlite_ ) {
         LOG_E( "databse ", db_name, "has been open previously" );
         return false;
      }

      sqlite3_open( db_name.c_str(), &sqlite_ );

      return true;
   }

   bool SqlSystem::create_db( std::string const & db_name, std::string const & sql_def_file )
   {
      return true;
   }

   bool SqlSystem::exist_db( std::string const & db_name ) const
   {
          /*
           * Exists db file and is valid
           */
      return true;
   }

   bool SqlSystem::update_db( std::string const & db_name, std::string const & sql_def_file )
   {
          // apply changes and updates db internal version to new one
      return true;
   }

   bool SqlSystem::search_for_updates() const
   {
          // checking if update file exists
          // then request user to perform update
      return true;
   }

   bool SqlSystem::execute_sql( std::string const & db_name ) const
   {
      return true;
   }

   bool SqlSystem::exist_update_file_() const
   {
      return true;
   }

}
