#include "Exception.h"

using namespace std;

namespace ak {

   ak_exception::ak_exception( string const & msg )
   : msg_( msg )
   {
   }

   const char* ak_exception::what() const throw()
   {
      return msg_.c_str();
   }

   ak_options_exception::ak_options_exception( string const & msg )
   : ak_exception( msg )
   {
   }

   ak_files_exception::ak_files_exception( string const & msg )
   : ak_exception( msg )
   {
   }


}


