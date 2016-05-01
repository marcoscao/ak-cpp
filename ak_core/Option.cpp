#include "Option.h"

namespace ak {

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

   void Option::execute() 
   {
   }


}



