#ifndef AK_FACTORY_H__
#define AK_FACTORY_H__

#include "Exception.h"
#include "Option.h"

#include <memory>
#include <unordered_map>
#include <vector>


namespace ak {

   template<typename T>
   class Factory {
   public:

     using RegFn = std::unique_ptr<T> (*)();
     using RegMap = std::unordered_map< int, RegFn >;
     using Instances = std::vector< std::shared_ptr< Option > >;
        

      static Factory & instance()
      {
         static Factory<T> f;
         return f;
      }


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

      std::shared_ptr<T> create( int id )
      {
         auto it = registered_.find( id );
         if( it == registered_.end() )
            throw ak_exception( "id: " + std::to_string(id) + " not registered while creating item" );
            
         std::unique_ptr<T> p = it->second();
         if( p == nullptr )
            throw ak_exception( "Something wrong creating item id: " + std::to_string(id) );

         //! TODO: change id registration way
         p->set_registered_id_( id );

         std::shared_ptr<Option> sp( std::move( p ) );
         instances_.push_back( sp );
           
         return sp;
      }

   private:
      static RegMap registered_;       // holds registered items
      static Instances instances_;     // stores created instances to later delete

      Factory() = default;             // private constructor
   };


   template<typename T>
   typename Factory<T>::RegMap Factory<T>::registered_ = Factory<T>::RegMap();

   template<typename T>
   typename Factory<T>::Instances Factory<T>::instances_ = Factory<T>::Instances();

}

#endif


