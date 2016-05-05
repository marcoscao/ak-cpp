#include "Utils.h"


#include <algorithm>
#include <cctype>
#include <sstream>

#ifndef _USING_CYGWIN_
	#include <boost/date_time.hpp>
#else
	#include <iostream>
#endif


using namespace std;

namespace ak { namespace util {


   std::string time_now()
   {

#ifndef _USING_CYGWIN_
      boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
      return boost::posix_time::to_iso_extended_string( now );
#else
	return "TODO on cygwin";
#endif

   }

   long to_kb( long bytes )
   {
      return bytes / 1024;
   }

   long to_mb( long bytes )
   {
      return to_kb( bytes ) / 1024;
   }

   long to_gb( long bytes )
   {
      return to_mb( bytes ) / 1024;
   }

   bool prompt_question( std::string const & msg, bool default_is_yes )
   {
      if( msg.empty() )
         cout << msg << " would you like to continue ";

      if( default_is_yes )
         cout << "( YES/no ) ? ";
      else
         cout << "( yes/NO ) ? ";

      string s;
      getline(cin,s);

      if( s.empty() || s == "" )
         return default_is_yes;

      std::transform( begin(s), end(s), begin(s), []( unsigned char c ){ return std::tolower(c); } );

      if( s=="y" or s=="yes" )
         return true;

      return false;
   }

} }

