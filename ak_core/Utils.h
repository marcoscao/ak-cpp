#ifndef AK_CORE_UTILS_H__
#define AK_CORE_UTILS_H__

#include <string>
#include <sstream>

namespace ak { namespace util {
   

   /*
    * Converts variadic values into a stringstream
    * Useful for logs and exceptions usage
    */
   class variadic_to_string {
   public:
      variadic_to_string( std::string const & separator = " " ) 
      :  separator_( separator ),
         buffer_() 
      {
      }

      std::stringstream & buffer()
      {
         return buffer_;
      }

      void clear_buffer()
      {
         buffer_.str( std::string() );
      }

      template< typename... Values>
      std::stringstream & values( Values const &... values ) 
      {
         buffer_.clear();

         perform_values_( values... );

         return buffer_;
      }

      
   private:
      std::string separator_;
      std::stringstream buffer_;

      //! dumps each item of the variadic template
      template< typename T >
      void perform_values_( T const & val )
      {
         buffer_ << val;
      }
	
      //! Variadic for simple and easy usage
      template< typename T, typename... Values>
      void perform_values_( T const & head, Values const &... values ) 
      {
         int n = sizeof...(Values);
         buffer_ << head << separator_;
         perform_values_( values... );
      }
   };


   //! Easy usage
   template< typename... Values>
   std::string var2str( Values const &... values ) 
   {
      ak::util::variadic_to_string v2s;
      return v2s.values( values... ).str();
   }




   /*
    * current date-time
    */
   std::string time_now();

   /*
    */
   long to_kb( long bytes );


   long to_mb( long bytes );
   

   long to_gb( long bytes );


} }

#endif

