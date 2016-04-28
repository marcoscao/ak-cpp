#include "OptionsFactory.h"

namespace ak {

   OptionsFactory::OptionsFactory()
   : ct_()
   {
   }

   OptionsFactory::OptionsFactory & instance()
   {
      static OptionsFactory of;
      return of;
   }

   void OptionsFactory::register_op( int id, RegFn fn )
   {
      auto it = ct_.find( id );
      if( it != ct_.end() )
         throw ak_exception( "id previously registered" );

      std::pair< RegMap::iterator, bool> p = ct_.insert( RegMap::value_type( id, fn ) );
      if( p == false )
         throw ak_exception( "something wrong trying to register option" );
   }

   Option * OptionsFactory::create_op( int id )
   {
      auto it = ct_.find( id );
      if( it == ct_.end() )
         throw ak_exception( "id not registered" );

      return it->second->create()
   }

}


