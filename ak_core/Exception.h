#ifndef AK_CORE_EXCEPTION_H__
#define AK_CORE_EXCEPTION_H__

#include <exception>
#include <string>

// #define THROW_E( ... ) \
// { \
//    std::string reserved__build__str__from__variadic__ = ak::util::var2str( __VA__ARGS__ ); \
//    LOG_E( reserved__build__str__from__variadic__ ); \
//    throw ak::ak_exception( reserved__build__str__from__variadic__ ); \
// } \
//

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

