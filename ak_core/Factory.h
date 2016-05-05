#ifndef AK_FACTORY_H__
#define AK_FACTORY_H__

#include "Exception.h"
#include "Option.h"

#include <memory>
#include <unordered_map>
#include <vector>


namespace ak {

   template<typename T>
   class factory {
   public:

     using RegFn = T * (*)();
     using RegMap = std::unordered_map< int, RegFn >;
     using Instances = std::vector< std::shared_ptr< Option > >;
        

      /*
       * Register items
       */
      virtual void registrar();


      // void register_item( int id, RegFn fn ) 
      // {
      //     auto it = registered_.find( id );
      //
      //     if( it != registered_.end() )
      //        throw ak_exception( "id: " + std::to_string( id ) + " previously registered while registering item" );
      //
      //    std::pair< typename RegMap::iterator, bool> p = registered_.insert( typename RegMap::value_type( id, fn ) );
      //    if( p.second == false )
      //       throw ak_exception( "Something wrong trying to register option id: " + std::to_string(id) );
      // }

      /*
       * Register item id
       * typename D = is the class to automatically attach "callback" to the create() method
       */
      template< typename D >
      void register_item( int id ) 
      {
          auto it = registered_.find( id );

          if( it != registered_.end() )
             throw ak_exception( "id: " + std::to_string( id ) + " previously registered while registering item" );

         // Set the default callback function as D::create
         RegFn fn = D::create;
         std::pair< typename RegMap::iterator, bool> p = registered_.insert( typename RegMap::value_type( id, fn ) );
         if( p.second == false )
            throw ak_exception( "Something wrong trying to register option id: " + std::to_string(id) );
      }

      bool is_registered( int id ) const
      {
         return false;
      }

      T * create( int id )
      {
         auto it = registered_.find( id );
         if( it == registered_.end() )
            throw ak_exception( "id: " + std::to_string(id) + " not registered while creating item" );
            
         T * p = it->second();
         if( p == nullptr )
            throw ak_exception( "Something wrong creating item id: " + std::to_string(id) );

         p->set_registered_id_( id );

         instances_.push_back( std::shared_ptr<T>( p ) );
           
         return p;
      }

   private:
      static RegMap registered_;
      static Instances instances_;				// stores created instances to later delete

   };


   template<typename T>
   typename factory<T>::RegMap factory<T>::registered_ = factory<T>::RegMap();

   template<typename T>
   typename factory<T>::Instances factory<T>::instances_ = factory<T>::Instances();

}

#endif


