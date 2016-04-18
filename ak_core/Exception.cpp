#include "Exception.h"

using namespace std;

namespace ak {

   AkException::AkException( string const & msg )
   : msg_( msg )
   {
   }

   const char* AkException::what() const throw()
   {
      return std::string( "ak_exception: " + msg_ ).c_str();
   }

}


