#ifndef AK_CORE_UTILS_H__
#define AK_CORE_UTILS_H__

#include <string>

namespace ak {

   std::string time_now();

   long to_kb( long bytes );

   long to_mb( long bytes );
   
   long to_gb( long bytes );

}

#endif

