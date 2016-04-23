#ifndef AK_CORE_LOGSYSTEM_H__
#define AK_CORE_LOGSYSTEM_H__

#include "Utils.h"

#include <iostream>
#include <fstream>
#include <sstream>


#define LOG_T( ... ) { ak::ak_log( LogSystem::Level::Trace, __VA_ARGS__ ); }
#define LOG_D( ... ) { ak::ak_log( LogSystem::Level::Debug, __VA_ARGS__ ); }
#define LOG_W( ... ) { ak::ak_log( LogSystem::Level::Warning, __VA_ARGS__ ); }
#define LOG_I( ... ) { ak::ak_log( LogSystem::Level::Info, __VA_ARGS__ ); }
#define LOG_E( ... ) { ak::ak_log( LogSystem::Level::Error, __VA_ARGS__ ); }


namespace ak {

   class LogSystem {
   public:
      enum class Level {
         Trace = 0,
         Debug,
         Warning,
         Info,
         Error
      };
      

      ~LogSystem()
      {
         fs_.flush();
         fs_.close();
      }

      void initialize( std::string const & file_name, Level level )
      {
         fs_.open( file_name.c_str(), std::ios_base::app | std::ios_base::out );
         
         current_level_ = level;
         log( current_level_, "Starting log with log level", level_to_string(level) );
      }

      static LogSystem & get( )
      {
	static LogSystem l;
	return l;
      }

      std::stringstream & buffer() 
      {
         return buffer_;
      }

      void clear_buffer()
      {
         buffer_.str( std::string() );
      }

      std::string level_to_string( Level level)
      {
         switch(level) {
            case Level::Trace : return "TRACE";
            case Level::Debug : return "DEBUG";
            case Level::Warning : return "WARNING";
            case Level::Info : return "INFO";
            case Level::Error : return "ERROR";
            };

         return "UNKNOW";
      }
      
      //! Variadic for simple and easy usage
      template< typename... Values>
      void log( Level level, Values const &... values ) 
      {
         if( level < current_level_ )
            return;

         clear_buffer();

         buffer_ << "[ " << level_to_string(level) << " ] ";
         buffer_ << time_now() << " : ";

         log_item_( values... );
 
         fs_ << buffer_.str() << std::endl;

         std::cout << buffer_.str() << std::endl;

	 //std::cout << std::endl;
      }

      //! dumps each item of the variadic template
      template< typename T >
      void log_item_( T const & val )
      {
         buffer_ << val;
      }
	

      //! Variadic for simple and easy usage
      template< typename T, typename... Values>
      void log_item_( T const & head, Values const &... values ) 
      {
         int n = sizeof...(Values);
	 
         buffer_ << head << " ";
         log_item_( values... );
      }


   private:
      Level current_level_;
      std::ofstream fs_;
      std::stringstream buffer_;

      LogSystem()
      :  current_level_( Level::Trace ),
         fs_(),
         buffer_()
      {
      }
      
   };

   
   //! Alias for easy usage
   template< typename... Values>
   void ak_log( LogSystem::Level level, Values const &... values ) 
   {
      LogSystem::get().log( level, values... );
   }

   
} // end namespace

#endif

