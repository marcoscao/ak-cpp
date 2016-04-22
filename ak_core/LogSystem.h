#ifndef AK_CORE_LOGSYSTEM_H__
#define AK_CORE_LOGSYSTEM_H__

#include <iostream>


namespace ak {

//	class LogSystem {
//	public:
////		LogSystem & get( std::string const & base_log_filename = "app" )
////		{
////			static LogSystem l( base_log_filename );
////			return &l;
////		}
////
//		~LogSystem();
//
//		static void initialize( std::string const & file_name, int level = 0 );
//
//
//
//	private:
//		int current_level_;
//
//		LogSystem();
////
////		void initialize_();
//	};
//
//
//	template<typename T>
//	std::ostream & operator<<( std::ostream & os, T const & val )
//	{
//		os << val;
//		return os;
//	}

//	void ak_log_initialize( std::string const & file_name, int level )
//	{
//		LogSystem & log = LogSystem::get();
//		log.initialize( "default.log", 1 );
//	}

	
	//! dumps each item of the variadic template
	template< typename T >
	void ak_log_item_( T const & val )
	{
		std::cout << val;
	}

	//! Variadic for simple and easy usage
	template< typename T, typename... Values>
	void ak_log_item_( T const & head, Values const &... values ) 
	{
		int n = sizeof...(Values);

		//std::cout << "[ " << level << " ] ";
		std::cout << head;
		ak_log_item_( values... );
 
		//	for( int i = 0; i < sizeof...(Values); ++i )
		//		std::cout << 
		
		//std::cout << std::endl;
	}

	//! Variadic for simple and easy usage
	template< typename... Values>
	void ak_log( int level, Values const &... values ) 
	{
		std::cout << "[ " << level << " ] ";
		ak_log_item_( values... );
 
		//	for( int i = 0; i < sizeof...(Values); ++i )
		//		std::cout << 
		
		std::cout << std::endl;

	}



}

#endif

