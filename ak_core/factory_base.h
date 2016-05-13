#ifndef AK_CORE_FACTORY_BASE_H__
#define AK_CORE_FACTORY_BASE_H__

#include <memory>

namespace ak {
	
   
   class factory_item_base {
      
      template<typename> friend class factory;

   public:
      int registered_id() const
      {
         return id_;
      }

   private:
      int id_;

      void set_registered_id(int id) 
      {
         id_ = id;
      }
   };

   

   class factory_item_creator_base;


   class factory_base {
   public:
	   /*
	    * register item with passed id
	   */
	   virtual void register_item( int id, std::unique_ptr< factory_item_creator_base > ) = 0;

	   virtual std::shared_ptr< factory_item_base > create_item( int id ) = 0;

   protected:
	   factory_base() = default;
	   virtual ~factory_base() = default;
   };



   class factory_item_creator_base {
   public:
	   factory_item_creator_base() = default;
	   virtual ~factory_item_creator_base() = default;

	   virtual std::unique_ptr< factory_item_base > operator()() = 0;
   };


}

#endif


