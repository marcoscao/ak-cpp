#include "ProgramOptionsBase.h"
#include "Command.h"
#include "Exception.h"

#include <iostream>


using namespace std;
namespace po = boost::program_options;

namespace ak {

   PO::PO()
   :  bpo_desc_( "Available Options" ),
      bpo_positional_(),
      bpo_vm_(),
      option_invokers_()
   {
   }

   PO::~PO()
   {
      //! TODO: Clean created options ?
   }

   void PO::execute( int argc, char** argv )
   {
      // verify/check passed options
      process_command_line_arguments( argc, argv );


      // iterate over known options to call callbacks
      for( auto it = begin( option_invokers_ ); it != end( option_invokers_); ++it ) {

      	//cout << "core:: iterating over option name:  " << it->first << endl; 
        
         if( has_option( it->first ) ) {

            //cout << "core:: found option " << it->first << endl; 
            if( it->second.first ) {
               cout << "core:: launching callback for option: " << it->first << endl; 
               it->second.first();
            }

	    if( it->second.second ) {
               cout << "core:: launching Command for option: " << it->first << endl; 
	       it->second.second->execute( *this );
	    }
         }
      }
   }

   void PO::add_group( string const & title, option_def_list const & v )
   {
      po::options_description d( title.c_str() );

      for( auto i : v ) {

         mapping_option_invokers_( i );

         if( get<2>(i.data_) ) {
            //cout << get<0>(i.data_) << " is alive" << endl;
            d.add_options()( get<0>(i.data_).c_str(), get<2>(i.data_), get<1>(i.data_).c_str() );
         }
         else {
            //cout << get<0>(i.data_) << " has NULL data" << endl;
            d.add_options()( get<0>(i.data_).c_str(), get<1>(i.data_).c_str() );
         }
      }

      bpo_desc_.add( d );
   }

   void PO::add_positional( string const & i, int num_ocurrences )
   {
      auto it = option_invokers_.find( i );
      if( it != option_invokers_.end() ) {
         //cout << "added option " << i << " as positional" << endl;
	 bpo_positional_.add( i.c_str(), num_ocurrences );
      }
   }

   void PO::add_positional( std::vector< std::string > const & v )
   {
      for( auto i : v ) 
         add_positional( i );
   }

   bool PO::has_option( std::string const & op_name ) const
   {
      return bpo_vm_.count( op_name );
   } 

   bool PO::no_user_option( ) const
   {
      return bpo_vm_.empty();
   } 

   void PO::print_usage( std::string const & title ) const
   {	
      //cout << title << "  usage " << endl;
      cout << bpo_desc_ << endl;
   }

   //void PO::process_command_line( int argc, char** argv )
   void PO::process_command_line_arguments( int argc, char** argv )
   {
      try {
         // could throw
         po::store(  po::command_line_parser( argc, argv )
                     .options( bpo_desc_ ).positional( bpo_positional_ ).run(),
                     bpo_vm_ ); 

         // just in case correct usage check if user asks for help
         if( bpo_vm_.count("help" ) || bpo_vm_.empty() ) {
      	    // trigger user callback if it is possible
	    auto it = option_invokers_.find( "help" );
	    if ( it != option_invokers_.end() && it->second.first ) {
	       it->second.first();
	       exit(0);
	    }
         }

         // throws on error
         po::notify( bpo_vm_ ); 
      } 
      catch( po::required_option & e ) { 
         string s = "Error! Not found some of the required options.\nPlease run again using --help to show available options.";
         s += "\n\n" + string( e.what() ) + " \n"; 
         throw ak_options_exception( s );
      } 
      catch( po::error & e ) { 
         string s = "Error! Something wrong. \nPlease run again using --help to show available options";
         s += "\n\n " + string( e.what() ) + " \n"; 
         throw ak_options_exception( s );
      } 
      catch( exception & e ) { 
         throw ak_options_exception( "Oops! something wrong with STL doing program options\n\n" + string( e.what() ) + " \n" );
      } 
   }

    void PO::mapping_option_invokers_( option_def const & op )
    {
      // splits "option_name" into ( large, short ) and store twice for internal purposes ( callbacks, etc... )
      // boost user stores option as one of: ",v" ,  "verbose" or  "verbose,v"
      // which will be called as:  "-v", "verbose", "verbose"
        
      string s = get< 0 >( op.data_ );
      CallbackFn const & c_fn = get< 3 >( op.data_ );
      CommandPtr const & p_cmd = get< 4 >( op.data_ );

      size_t pos = s.find_first_of( "," );
      if( pos != string::npos ) {
                
         // short way
         option_invokers_.insert( std::make_pair( "-" + s.substr(pos+1,1), make_pair( c_fn, p_cmd ) ) ); //get<3>(i.data_) ) );
            
         if( pos ) {
            // both large and short, so add the large way
            option_invokers_.insert( std::make_pair( s.substr(0, pos), make_pair( c_fn, p_cmd ) ) ); //get<3>(i.data_) ) );
         }
      }
      else {
         // it's a large option-name, store as it is
         option_invokers_.insert( std::make_pair( s, make_pair( c_fn, p_cmd ) ) ); //get<3>(i.data_) ) );
      }
    }

    
    //
   //
   // void PO::mapping_option_command_( option_def const & i )
   // {
	// 	 // splits "option_name" into ( large, short ) and store twice for internal purposes ( callbacks, etc... )
	// 	 // boost user stores option as one of: ",v" ,  "verbose" or  "verbose,v"
	// 	 // which will be called as:  "-v", "verbose", "verbose"
	// 	 
	// 	 string s = get<0>(i.data_);
   //
	// 	 size_t pos = s.find_first_of( "," );
	// 	 if( pos != string::npos ) {
	// 		 
	// 		// short way
	// 		options_commands_.insert( std::make_pair( "-" + s.substr(pos+1,1), get<4>(i.data_) ) );
	// 		
	// 		if( pos ) {
	// 			// both large and short, so add the large way
	// 			options_callbacks_.insert( std::make_pair( s.substr(0, pos), get<4>(i.data_) ) );
	// 		}
	// 	 }
	// 	 else {
	// 		// it's a large option-name, store as it is
	// 		options_callbacks_.insert( std::make_pair( s, get<4>(i.data_) ) );
	// 	 }
   // }
		 
}



