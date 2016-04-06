#ifndef AK_GENERATE_PROGRAM_OPTIONS__
#define AK_GENERATE_PROGRAM_OPTIONS__

#include "core/ProgramOptionsBase.h"

namespace ak {

   class ProgramOptions : public ProgramOptionsBase {
   public:		
      ProgramOptions() = default;

      virtual void help();

   };

}

#endif

