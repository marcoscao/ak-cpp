#ifndef AK_CORE_APP_MANAGER_H__
#define AK_CORE_APP_MANAGER_H__

#include "Factory.h"
#include <memory>
#include <string>

namespace ak {

   class Option;
   class PO;
   
   class AppManager {
   public:
      AppManager();

      void set_options_parser( ParseOptionsBase * p );

      void add_options( std::vector<int> const & ids, std::string const & group_title );

      void execute( int argc, char** argv );
           
   private:
      std::shared_ptr< factory<Option> > factory_;
      std::shared_ptr< ParseOptionsBase > parser_;
   };

}

#endif

