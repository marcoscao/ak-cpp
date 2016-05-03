#include "Command.h"
#include "Visitor.h"

namespace ak {

   Command::Command()
   : registered_id_( 0 )
   {
   }
   
   int Command::registered_id() const
   {
      return registered_id_;
   }

   void Command::set_registered_id_( int id )
   {
      registered_id_ = id;
   }

   std::string Command::name() 
   { 
      return "no - name"; 
   }

   void Command::accept( VisitorCmd & v ) 
   { 
      v.visit( *this );
   }

}



