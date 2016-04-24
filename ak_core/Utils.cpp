#include "Utils.h"
#include <boost/date_time.hpp>

namespace ak { namespace util {


   std::string time_now()
   {
      boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
      return boost::posix_time::to_iso_extended_string( now );
   }

   long to_kb( long bytes )
   {
      return bytes / 1024;
   }

   long to_mb( long bytes )
   {
      return to_kb( bytes ) / 1024;
   }

   long to_gb( long bytes )
   {
      return to_mb( bytes ) / 1024;
   }

} }

