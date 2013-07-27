#ifdef BOOST_MSVC
# pragma warning(disable: C4345)
#endif

#include <boost/test/test_tools.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/range_c.hpp>
#include "DownloaderFacade.hxx"

using boost::unit_test::test_suite;

BOOST_TEST_CASE_TEMPLATE_FUNCTION( foo, Number )
{
	BOOST_CHECK_EQUAL(2, 2);
}

test_suite * init_unit_test_suite( int, char * [] ) 
{
    test_suite * test = BOOST_TEST_SUITE( "Experimental" );

    typedef boost::mpl::range_c<int, 0, 10> numbers;

    test->add( BOOST_TEST_CASE_TEMPLATE( foo, numbers ) );

    return test;
}