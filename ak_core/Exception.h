#ifndef AK_CORE_EXCEPTION_H__
#define AK_CORE_EXCEPTION_H__

#include <exception>
#include <string>

namespace ak {

   class ak_exception : public std::exception {
   public:
      ak_exception( std::string const & msg );

      virtual const char* what() const throw();

   private:
      std::string msg_;
   };


   class ak_options_exception : public ak_exception {
   public:
      ak_options_exception( std::string const & msg );
   };
   

   class ak_files_exception : public ak_exception {
   public:
      ak_files_exception( std::string const & msg );
   };

}

#endif

