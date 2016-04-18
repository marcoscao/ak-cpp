#ifndef AK_CORE_EXCEPTION_H_
#define AK_CORE_EXCEPTION_H_

#include <exception>
#include <string>

namespace ak {
   class AkException : public std::exception {
   public:
      AkException( std::string const & msg );

      virtual const char* what() const throw();

   private:
      std::string msg_;
   };

}

#endif

