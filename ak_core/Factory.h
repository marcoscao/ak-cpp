#ifndef AK_FACTORY_H__
#define AK_FACTORY_H__

#include "Exception.h"
#include "Option.h"

#include <memory>
#include <unordered_map>
#include <vector>


namespace ak {

   class option_creator;


   template<typename T>
   class Factory {
   public:

     using RegFn = std::unique_ptr<T> (*)();
     using RegMap = std::unordered_map< int, RegFn >;
      //using AA = std::unique_ptr< option_creator >;
     using RegMap_v2 = std::unordered_map< int, std::unique_ptr< option_creator > >;
     using Instances = std::vector< std::shared_ptr< Option > >;
        

      static Factory & instance()
      {
         static Factory<T> f;
         return f;
      }

	
      void register_item_v2( int id, std::unique_ptr< option_creator > op_creator )
       {
          auto it = registered_v2_.find( id );

          if( it != registered_v2_.end() )
             throw ak_exception( "v2: id: " + std::to_string( id ) + " previously registered while registering item" );

         // Set the default callback function as D::create
         //RegFn fn = D::create;
         std::pair< typename RegMap_v2::iterator, bool> p = registered_v2_.insert( typename RegMap_v2::value_type( id, std::move( op_creator ) ) );
         if( p.second == false )
            throw ak_exception( "v2: Something wrong trying to register option id: " + std::to_string(id) );

       }


      /*
       * Register item id
       * typename D = is the class to automatically attach "callback" to the create() method
       */
      // template< typename D >
      // void register_item( int id ) 
      // {
      //     auto it = registered_.find( id );
      //
      //     if( it != registered_.end() )
      //        throw ak_exception( "id: " + std::to_string( id ) + " previously registered while registering item" );
      //
      //    // Set the default callback function as D::create
      //    RegFn fn = D::create;
      //    std::pair< typename RegMap::iterator, bool> p = registered_.insert( typename RegMap::value_type( id, fn ) );
      //    if( p.second == false )
      //       throw ak_exception( "Something wrong trying to register option id: " + std::to_string(id) );
      // }

      // bool is_registered( int id ) const
      // {
      //    return false;
      // }

      // std::shared_ptr<T> create( int id )
      // {
      //    auto it = registered_.find( id );
      //    if( it == registered_.end() )
      //       throw ak_exception( "id: " + std::to_string(id) + " not registered while creating item" );
      //       
      //    std::unique_ptr<T> p = it->second();
      //    if( p == nullptr )
      //       throw ak_exception( "Something wrong creating item id: " + std::to_string(id) );
      //
      //    //! TODO: change id registration way
      //    p->set_registered_id_( id );
      //
      //    std::shared_ptr<Option> sp( std::move( p ) );
      //    instances_.push_back( sp );
      //      
      //    return sp;
      // }

      std::shared_ptr<Option> create_v2( int id );
      // {
      //    auto it = registered_v2_.find( id );
      //    if( it == registered_v2_.end() )
      //       throw ak_exception( "v2: id: " + std::to_string(id) + " not registered while creating item" );
      //       
      //    std::unique_ptr< Option > p = it->second->create(); //it->second();
      //    if( p == nullptr )
      //       throw ak_exception( "v2: Something wrong creating item id: " + std::to_string(id) );
      //
      //    //! TODO: change id registration way
      //    //p->set_registered_id_( id );
      //
      //    std::shared_ptr< Option > sp( std::move( p ) );
      //    instances_.push_back( sp );
      //      
      //    return sp;
      // }

   private:
      static RegMap registered_;       // holds registered items
      static RegMap_v2 registered_v2_;       // holds registered items
      static Instances instances_;     // stores created instances to later delete

      Factory() = default;             // private constructor
   };



   template<typename T>
   typename Factory<T>::RegMap Factory<T>::registered_ = Factory<T>::RegMap();

   template<typename T>
   typename Factory<T>::RegMap_v2 Factory<T>::registered_v2_ = Factory<T>::RegMap_v2();

   template<typename T>
   typename Factory<T>::Instances Factory<T>::instances_ = Factory<T>::Instances();




   class option_creator {
   public:
      option_creator( int id ) 
      {
      }

      virtual ~option_creator() = default;

      virtual std::unique_ptr< Option > create( ) = 0;
   };




   template<typename T>
	class option_creator_impl : public option_creator {
	public:
		option_creator_impl(int id ) 
		: option_creator( id )
		{
	  		Factory<Option>::instance().register_item_v2( id, 
				std::unique_ptr<option_creator>( new option_creator_impl<T>( *this ) ) );
		}

		virtual std::unique_ptr< Option > create()
		{
			return std::make_unique<T>();
		}	
	};



   template<typename T>
   std::shared_ptr<Option> Factory<T>::create_v2(int id )
      {
         auto it = registered_v2_.find( id );
         if( it == registered_v2_.end() )
            throw ak_exception( "v2: id: " + std::to_string(id) + " not registered while creating item" );
            
         std::unique_ptr< Option > p = it->second->create(); //it->second();
         if( p == nullptr )
            throw ak_exception( "v2: Something wrong creating item id: " + std::to_string(id) );

         //! TODO: change id registration way
         //p->set_registered_id_( id );

         std::shared_ptr< Option > sp( std::move( p ) );
         instances_.push_back( sp );
           
         return sp;
      }


}

#endif


