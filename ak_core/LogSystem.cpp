#include "LogSystem.h"



//#include <boost/log/core.hpp>
//#include <boost/log/trivial.hpp>
//#include <boost/log/expressions.hpp>
//#include <boost/log/sinks/text_file_backend.hpp>
//#include <boost/log/utility/setup/file.hpp>
//#include <boost/log/utility/setup/common_attributes.hpp>
//#include <boost/log/sources/severity_logger.hpp>
//#include <boost/log/sources/record_ostream.hpp>
//
//namespace logging = boost::log;
//namespace src = boost::log::sources;
//namespace sinks = boost::log::sinks;
//namespace keywords = boost::log::keywords;
//
//
//namespace ak {
//	LogSystem::LogSystem( string const & base_log_filename )
//	: base_log_filename_( base_log_filename )
//	{
//		initialize_();
//	}
//
//	void LogSystem::initializa()
//	{
//		logging::add_file_log (
//        	keywords::file_name = base_log_filename_ + "_%N.log",   /*< file name pattern >*/
//        	keywords::rotation_size = 10 * 1024 * 1024,             /*< rotate files every 10 MiB... >*/
//        	//keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0), 		/*< ...or at midnight >*/
//        	keywords::format = "[%TimeStamp%]: %Message%"                                 			/*< log record format >*/
//    	);
//
//    	logging::core::get()->set_filter (
//    		logging::trivial::severity >= logging::trivial::info
//    	);
//	}
//
//
//}

