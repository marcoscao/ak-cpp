#include "AppManager.h"
#include "Exception.h"
#include "Factory.h"
#include "LogSystem.h"
#include "Option.h"

using namespace std;


namespace ak {

   AppManager::AppManager()
   {
   }

   void AppManager::set_options_parser( ParseOptionsBase * p )
   {
      LOG_I( "Setting ParserOptions" )

      if( p == nullptr )
         throw ak_exception("null parser_options object");

      parser_ = std::shared_ptr< ParseOptionsBase >( p );

      // Call to register user options
      //parser_->register_options( *factory_ );
      // parser_->register_options( );
   }

   void AppManager::add_options( std::vector<int> const & ids, std::string const & group_title )
   {
      LOG_I( "Creating registered options" )
      std::vector< std::shared_ptr< Option > > v;

      for( auto i : ids ) {
         LOG_I( "Creating option id:", i )
         //v.push_back( factory_->create( i ) );
         //v.push_back( Factory<Option>::instance().create_v2( i ) );
         v.push_back( static_pointer_cast< Option >( get_options_factory().create_item( i ) ) );
         
      }

      LOG_I( "Adding those created options to group:",group_title )
      parser_->add_group( group_title, v );
   }

   void AppManager::execute( int argc, char** argv )
   {
      LOG_I( "Processing command line arguments:", argv )
         
      // let boost do the first processing stuff
      parser_->process_command_line_arguments( argc, argv );

      LOG_I("Start executing entered user options..." )
      
      parser_->execute();

      LOG_I("End execution of entered user options" )
   }

   ParseOptionsBase & AppManager::options_parser( )
   {
      return *parser_;
   }
        
}


