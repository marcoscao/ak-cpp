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

#define LOG_CONSOLE( ... ) { LogSystem::get().log_console( __VA_ARGS__ ); }


namespace ak {

   class LogSystem {
   public:
      enum class Level {
         Trace = 0,
         Debug,
         Warning,
         Info,
         Error,
         Console
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

      std::string level_to_string( Level level)
      {
         switch(level) {
            case Level::Trace : return "TRACE";
            case Level::Debug : return "DEBUG";
            case Level::Warning : return "WARNING";
            case Level::Info : return "INFO";
            case Level::Error : return "ERROR";
            case Level::Console : return "CONSOLE";
            };

         return "UNKNOW";
      }
      
      //! Variadic for simple and easy usage
      template< typename... Values>
      void log( Level level, Values const &... values ) 
      {
         if( level < current_level_ )
            return;

         v2s_.clear_buffer();

         v2s_.values( "[", level_to_string(level),"]", ak::util::time_now(), "| " );
 
         v2s_.values( values... );

         fs_ << v2s_.buffer().str() << std::endl;
         //std::cout << v2s_.buffer().str() << std::endl;
      }

      //! specialization dumping to console
      template< typename... Values>
      void log_console( Values const &... values ) 
      {
         v2s_.clear_buffer();
         v2s_.values( values... );
         std::cout << v2s_.buffer().str() << std::endl;
      }


   private:
      Level current_level_;
      std::ofstream fs_;
      ak::util::variadic_to_string v2s_;

      LogSystem()
      :  current_level_( Level::Trace ),
         fs_(),
         v2s_()
      {
      }
      
   };

   
   //! Alias for easy usage
   template< typename... Values>
   void ak_log( LogSystem::Level level, Values const &... values ) 
   {
      LogSystem::get().log( level, values... );
      
      if( level == LogSystem::Level::Error || level == LogSystem::Level::Console )
         LogSystem::get().log_console( values... );
         
      //LogSystem::get().log_console( values... );
   }

   
} // end namespace

#endif

