#include "ProgramOptionsBase.h"
#include <iostream>

using namespace std;
namespace po = boost::program_options;

namespace ak {

   PO::PO()
   :  bpo_desc_( "Available Options" ),
      bpo_positional_(),
      bpo_vm_(),
	  options_callbacks_()
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
      for( auto it = begin( options_callbacks_ ); it != end( options_callbacks_); ++it ) {
         if( has_option( it->first ) ) {
            //cout << "core:: found option " << it->first << endl; 
            if( it->second ) {
               //cout << "core:: launching callback " << it->first << endl; 
               it->second();
            }
         }
      }
   }

   void PO::add_group( string const & title, option_def_list const & v )
   {
      po::options_description d( title.c_str() );

      for( auto i : v ) {

         // insert each option for internal management purposes
		 options_callbacks_.insert( std::make_pair( get<0>(i.data_), get<3>(i.data_) ) );

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
		auto it = options_callbacks_.find( i );
		if( it != options_callbacks_.end() ) {
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
         if( bpo_vm_.count("help" ) ) {
      		// trigger user callback if it is possible
			auto it = options_callbacks_.find( "help" );
			if ( it != options_callbacks_.end() && it->second ) {
				it->second();
				exit(0);
			}
         }

         // throws on error
         po::notify( bpo_vm_ ); 
      } 
      catch( po::required_option & e ) { 
         cout << endl << "Error! Not found some of the required options. Please run again using --help to show available options" << endl;
         cerr << e.what() << std::endl << std::endl; 
         abort();
      } 
      catch( po::error & e ) { 
         cout << endl << "Error! Something wrong. Please run again using --help to show available options" << endl;
         cerr << e.what() << std::endl << std::endl; 
         abort();
      } 
      catch( exception & e ) { 
         cout << endl << "Oops! stl exception" << endl;
         cerr << e.what() << std::endl << std::endl; 
         abort();
      } 
   }

}



