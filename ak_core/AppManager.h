#ifndef AK_CORE_APP_MANAGER_H__
#define AK_CORE_APP_MANAGER_H__

#include "Factory.h"
#include <memory>
#include <string>
#include <vector>

namespace ak {
   
   class AppManager {
   public:
      AppManager();

      void set_options_parser( ParseOptionsBase * p );

      void add_options( std::vector<int> const & ids, std::string const & group_title );

      void execute( int argc, char** argv );

      ParseOptionsBase & options_parser( );
           
   private:
      //std::shared_ptr< factory<Option> > factory_;
      std::shared_ptr< ParseOptionsBase > parser_;

      static const std::vector<std::string> ff_;
   };

   //const std::string AppManager::ff_ = std::string("jkjkj"); 
}

#endif

