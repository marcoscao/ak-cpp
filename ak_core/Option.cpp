#include "Option.h"

namespace ak {

   Option::Option()
   : registered_id_( 0 )
   {
   }
   
   int Option::registered_id() const
   {
      return registered_id_;
   }

   void Option::set_registered_id_( int id )
   {
      registered_id_ = id;
   }

   std::string Option::name() 
   { 
      return "no - name"; 
   }

   std::string Option::description() 
   { 
      return "no - description"; 
   }

   ParseOptionsBase::StorageType * Option::storage_type() 
   { 
      return nullptr; 
   }

}



