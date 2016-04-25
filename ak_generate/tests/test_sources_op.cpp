#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE AkGenerateSuites

#include <boost/test/unit_test.hpp>
#include "../ProgramOptions.h"


BOOST_AUTO_TEST_SUITE( test_command_line )

BOOST_AUTO_TEST_CASE( sources_option )
{
    //my_class test_object( "qwerty" );
	ak::gen::ProgramOptions po;
	po.initialize();
	//po.command_line_arguments( argc, argv );

    BOOST_CHECK( po.has_option( "source-path" )  );
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE( test_operations )

BOOST_AUTO_TEST_SUITE_END()

