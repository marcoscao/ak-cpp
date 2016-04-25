#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE AkGenerateSuites

#include <boost/test/unit_test.hpp>
#include "../ProgramOptions.h"

struct PoFixture {
   
   PoFixture() 
   { 
      BOOST_TEST_MESSAGE( "setup fixture" ); 
   }
   
   ~PoFixture()         
   { 
      BOOST_TEST_MESSAGE( "teardown fixture" ); 
   }
};



BOOST_FIXTURE_TEST_SUITE( test_command_line, PoFixture )


BOOST_AUTO_TEST_CASE( no_command_line_options )
{
   ak::gen::ProgramOptions po;
   po.initialize();
      
   // [0] is the executable name
   //const int argc = 1;   
   //const char* argv[ argc ] = {  "app_name" };
   //po.process_command_line_arguments( argc, const_cast<char**>( argv ) );

   BOOST_CHECK( po.has_option( "source-path" ) == false );
   BOOST_CHECK( po.has_option( "verbose" ) == false );
   BOOST_CHECK( po.has_option( "dry-run" ) == false );
}


BOOST_AUTO_TEST_CASE( has_sources_option )
{
   ak::gen::ProgramOptions po;
   po.initialize();
      
   // [0] is the executable name
   const int argc = 3;   
   const char* argv[ argc ] = {  "app_name", "--source-path", "/Volu" };
   po.process_command_line_arguments( argc, const_cast<char**>( argv ) );

   BOOST_CHECK( po.has_option( "source-path" )  );
}

BOOST_AUTO_TEST_CASE( has_verbose_option )
{
   ak::gen::ProgramOptions po;
   po.initialize();
      
   // [0] is the executable name
   const int argc = 2;   
   const char* argv[ argc ] = {  "app_name", "--verbose" };
   po.process_command_line_arguments( argc, const_cast<char**>( argv ) );

   BOOST_CHECK( po.has_option( "verbose" )  );
}


BOOST_AUTO_TEST_CASE( has_multiple_sources_option )
{
   ak::gen::ProgramOptions po;
   po.initialize();
      
   // [0] is the executable name
   const int argc = 7;   
   const char* argv[ argc ] = {  "app_name", 
                                 "--source-path", "/Volu/A",
                                 "--source-path", "/Volu/B", 
                                 "--source-path", "/Volu/C", 
                     };
   
   po.process_command_line_arguments( argc, const_cast<char**>( argv ) );

   BOOST_CHECK( po.has_option( "source-path" )  );
}


BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE( test_operations )

BOOST_AUTO_TEST_SUITE_END()

