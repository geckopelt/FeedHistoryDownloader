#ifdef BOOST_MSVC
# pragma warning(disable: C4345)
#endif

#include <boost/test/test_tools.hpp>
#include <boost/test/test_case_template.hpp>
#include "Helpers/UrlArgs.hxx"
#include "Helpers/HttpHelper.hxx"

using boost::unit_test::test_suite;
using namespace FeedHistoryDownloader;

//----------------------------------------------------------------
void urlArgsTest()
{
	UrlArgs args;
	BOOST_CHECK_EQUAL(args.getArgs(), "");
	args.addArg("foo", "bar");
	BOOST_CHECK_EQUAL(args.getArgs(), "?foo=bar");
	args.addArg("titi", "toto");
	BOOST_CHECK_EQUAL(args.getArgs(), "?foo=bar&titi=toto");
	args.addArg("the_question", "42");
	BOOST_CHECK_EQUAL(args.getArgs(), "?foo=bar&titi=toto&the_question=42");
}

//----------------------------------------------------------------
void httpHelperIntegrationTest()
{
	const std::string res = HttpHelper().performGet("http://example.com", UrlArgs());
	// $TODO: check return value
}

//----------------------------------------------------------------
test_suite * init_unit_test_suite(int, char * []) 
{
    test_suite * test = BOOST_TEST_SUITE("AllTests");
    test->add(BOOST_TEST_CASE(urlArgsTest));
	test->add(BOOST_TEST_CASE(httpHelperIntegrationTest));
    return test;
}