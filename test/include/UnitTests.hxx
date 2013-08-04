#pragma once
#include <boost/filesystem.hpp>
#include "Helpers/Guards.hxx"
#include "Helpers/UrlArgs.hxx"
#include "Helpers/DateTimeHelpers.hxx"
#include "Jobs/CompletedJobsCache.hxx"
using namespace FeedHistoryDownloader;

BOOST_AUTO_TEST_SUITE(unitTests)
	//----------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(urlArgsTest)
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
    BOOST_AUTO_TEST_CASE(historicalDateToStringTest)
	{
        BOOST_CHECK_EQUAL("2013-07-15", HistoricalDate(2013, 07, 15).getAsString());
    }

	//----------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(historicalTimeToStringTest)
	{
        BOOST_CHECK_EQUAL("23:01:59", HistoricalTime(23, 01, 59).getAsString());
    }

    //----------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(historicalDateParseTest)
    {
        BOOST_CHECK_EQUAL("2013-07-15", DateTimeHelpers::parseDate("2013-07-15").getAsString());
        BOOST_CHECK_THROW(DateTimeHelpers::parseDate("2013-07"), std::exception);
        BOOST_CHECK_THROW(DateTimeHelpers::parseDate("ololo"), std::exception);
    }

    //----------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(historicalTimeParseTest)
    {
        BOOST_CHECK_EQUAL("13:51:07", DateTimeHelpers::parseTime("13:51:07").getAsString());
        BOOST_CHECK_EQUAL("13:51:07", DateTimeHelpers::parseTime("13:51:07.337").getAsString());
        BOOST_CHECK_THROW(DateTimeHelpers::parseTime("45:01"), std::exception);
        BOOST_CHECK_THROW(DateTimeHelpers::parseTime("ololo"), std::exception);
    }

    //----------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(completedJobsCacheTest)
    {
        // TODO: crude. Implement a wraper.
        const std::string testFileName("foo.cache");
        if (boost::filesystem::exists(testFileName))
        {
            boost::filesystem::remove(testFileName);
        }

        HistoricalDate date1(2013, 05, 06);
        HistoricalDate date2(2012, 03, 01);
        // TODO: cleanup temp file
        CompletedJobsCache cache;
        cache.load(testFileName); // Must not throw an exception
        BOOST_CHECK(!cache.isJobAlreadyCompleted(date1));
        BOOST_CHECK(!cache.isJobAlreadyCompleted(date2));
        cache.setJobCompleted(date1);
        BOOST_CHECK(cache.isJobAlreadyCompleted(date1));
        BOOST_CHECK(!cache.isJobAlreadyCompleted(date2));
        cache.setJobCompleted(date2);
        BOOST_CHECK(cache.isJobAlreadyCompleted(date1));
        BOOST_CHECK(cache.isJobAlreadyCompleted(date2));
        cache.save(testFileName);
        cache.load(testFileName);
        BOOST_CHECK(cache.isJobAlreadyCompleted(date1));
        BOOST_CHECK(cache.isJobAlreadyCompleted(date2));

        boost::filesystem::remove(testFileName);
    }
BOOST_AUTO_TEST_SUITE_END()
