#ifndef AK_GENERATE_PROGRAM_OPTIONS_BASE__
#define AK_GENERATE_PROGRAM_OPTIONS_BASE__


namespace ak {

   class ProgramOptionsBase {
   public:		
      ProgramOptionsBase() = default;

      virtual void help() = 0;
   };

}

#endif

