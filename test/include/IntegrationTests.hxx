#pragma once
#include <memory>
#include "Helpers/HttpHelper.hxx"
#include "Helpers/Guards.hxx"
#include "DataProviders/XivelyDataProvider.hxx"
#include "Configuration/Configuration.hxx"
using namespace FeedHistoryDownloader;

BOOST_AUTO_TEST_SUITE(integrationTests)
	//----------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(httpHelperIntegrationTest)
    {
        const std::vector<char> data = HttpHelper().performGet("http://example.com", UrlArgs());

        // Assume we're having a simple 8-bit ASCII text response here
	    const std::string res(data.begin(), data.end());
        BOOST_CHECK(res.npos != res.find("<html>"));
        BOOST_CHECK(res.npos != res.find("</html>"));
        BOOST_CHECK(res.npos != res.find("Example Domain"));

        BOOST_CHECK_THROW(HttpHelper().performGet("http://localhost/42", UrlArgs()), GuardException);
    }

	//----------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(xivelyDataProviderIntegrationTest)
    {
        std::auto_ptr<IHttpHelper> httpHelper(new HttpHelper());

        // Not a secret info :)
        XivelyDataProvider xively(httpHelper.get(), 23396, "k4QttapyY0DpMaEDn9gqX6ObEvg3wNIChlKGLNcqTS0");
        const IDataProvider::HistoricalData data = xively.getData(HistoricalDate(2013, 07, 15));
        BOOST_CHECK_EQUAL(96, data.size());
        BOOST_CHECK(0 < data[0].getValue());
    }

    // A simple smoke test for now. TODO: increase code coverage!
	//----------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(configurationLoaderIntegrationTest)
    {
        Configuration conf;
        conf.parse("../../test/data/fhd.ini");
        BOOST_CHECK_EQUAL(3, conf.getDatesToRequest().size());
        BOOST_CHECK_EQUAL("ololo", conf.getApiKey());
        BOOST_CHECK_EQUAL("C:\\foo", conf.getOutputDir());
        BOOST_CHECK_EQUAL(31337, conf.getFeedId());
        BOOST_CHECK_EQUAL("MyProfile", conf.getProfileName());
    }
BOOST_AUTO_TEST_SUITE_END()
