#include "ParseOptionsBase.h"
#include "Exception.h"
#include "LogSystem.h"
#include "Option.h"
#include "Visitor.h"

#include <iostream>


using namespace std;
namespace po = boost::program_options;

namespace ak {

   ParseOptionsBase::ParseOptionsBase()
   :  bpo_desc_( "available options" ),
      bpo_positional_(),
      bpo_vm_(),
      added_options_()
   {
   }

   ParseOptionsBase::~ParseOptionsBase()
   {
   }

   void ParseOptionsBase::add_group( string const & title, OptionsList const & v )
   {
      po::options_description d( title.c_str() );

      for( auto i : v ) {

         added_options_.insert( OptionsMap::value_type( i->registered_id(), i ) );

         if( i->storage_type() )
            d.add_options()( i->cmdline_id().c_str(), i->storage_type(), i->description().c_str() );
         else
            d.add_options()( i->cmdline_id().c_str(), i->description().c_str() );
      }

      bpo_desc_.add( d );
   }

   // void ParseOptionsBase::add_positional( string const & i, int num_ocurrences )
   // {
   //    auto it = option_invokers_.find( i );
   //    if( it != option_invokers_.end() ) {
   //       //cout << "added option " << i << " as positional" << endl;
	//  bpo_positional_.add( i.c_str(), num_ocurrences );
   //    }
   // }
   //
   // void ParseOptionsBase::add_positional( std::vector< std::string > const & v )
   // {
   //    for( auto i : v ) 
   //       add_positional( i );
   // }

   bool ParseOptionsBase::has_user_entered_option( int registered_id ) const
   {
      auto it = added_options_.find( registered_id );
      if( it == added_options_.end() )
         throw ak_exception("no registerd option id: " + std::to_string(registered_id) + " to check if it was entered by the user" );

      return bpo_vm_.count( it->second->name() );
   } 

   // bool ParseOptionsBase::execute_option_if( int registered_id, bool force ) 
   // {
   //    auto it = added_options_.find( registered_id );
   //    if( it == added_options_.end() )
   //       throw ak_exception("no registerd option id: " + std::to_string(registered_id) + " while trying to execute option" );
   //
   //    if( bpo_vm_.count( it->second->name() )  || force ) {
   //       it->second->execute( *this );
   //       return true;
   //    }
   //
   //    return false;
   // } 

   // bool ParseOptionsBase::has_user_entered_option( std::string const & op_name ) const
   // {
   //    return bpo_vm_.count( op_name );
   // } 

   bool ParseOptionsBase::no_user_options( ) const
   {
         // std::cout << "debug boost entered options size: " << bpo_vm_.size() << " items" << endl;
         // for( auto i : bpo_vm_ ) 
         //    std::cout << "itemm:  " << i.first << endl;

      return bpo_vm_.empty();
   } 

   void ParseOptionsBase::print_usage( std::string const & title ) const
   {	
      //cout << title << "  usage " << endl;
      cout << bpo_desc_ << endl;
   }
      
   // Option * ParseOptionsBase::option_ptr( int registered_id ) const
   // {
   //    auto it = added_options_.find( registered_id );
   //    if ( it == added_options_.end() )
   //       throw ak_exception( "no registered_id to get its option_ptr" );
   //
   //    return it->second;
   // }

   void ParseOptionsBase::process_command_line_arguments( int argc, char** argv )
   {
      try {
         // could throw
         po::store(  po::command_line_parser( argc, argv )
                     .options( bpo_desc_ ).positional( bpo_positional_ ).run(),
                     bpo_vm_ ); 
         
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

   void ParseOptionsBase::apply_visitor( Visitor & v )
   {
      LOG_D( "Applying visitor typeid:", typeid(v).name(), "to all the added options" )
      for( auto i : added_options_ ) {
         i.second->accept( v );
      }
   }
}



