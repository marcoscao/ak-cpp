#ifndef AK_CORE_FACTORY_BASE_H__
#define AK_CORE_FACTORY_BASE_H__

#include <memory>

namespace ak {
	
   
   class factory_item {
   };

   
   class factory_item_creator_base;

   class factory_base {
   public:
	   virtual void register_item( int id, std::unique_ptr< factory_item_creator_base > ) = 0;
	   virtual std::shared_ptr< factory_item > create_item( int id ) = 0;

   protected:
	   factory_base() = default;
	   virtual ~factory_base() = default;
   };



   class factory_item_creator_base {
   public:
	   factory_item_creator_base() = default;
	   virtual ~factory_item_creator_base() = default;

	   virtual std::unique_ptr< factory_item > operator()() = 0;
   };


}

#endif


