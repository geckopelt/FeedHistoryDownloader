#define _SCL_SECURE_NO_WARNINGS
#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/date_time/gregorian/gregorian_types.hpp>
#include "Helpers/DateTimeHelpers.hxx"
#include "Helpers/Guards.hxx"

namespace FeedHistoryDownloader
{
    //----------------------------------------------------------------
    HistoricalDate DateTimeHelpers::parseDate(const std::string & date)
    {
        const int YearPart = 0;
        const int MonthPart = 1;
        const int DayPart = 2;

        std::vector<std::string> parts;
        boost::split(parts, date, boost::is_any_of("-"));
        CHECK(3 == parts.size(), "Invalid historical date format");
        HistoricalDate result(
            boost::lexical_cast<int>(parts[YearPart]),
            boost::lexical_cast<int>(parts[MonthPart]),
            boost::lexical_cast<int>(parts[DayPart]));
        result.validate();
        return result;
    }

    //----------------------------------------------------------------
    HistoricalTime DateTimeHelpers::parseTime(const std::string & time)
    {
        const int HourPart = 0;
        const int MinutePart = 1;
        const int SecondPart = 2;

        std::vector<std::string> parts;
        boost::split(parts, time, boost::is_any_of(":."));
        CHECK(3 <= parts.size(), "Invalid historical time format");
        HistoricalTime result(
            boost::lexical_cast<int>(parts[HourPart]),
            boost::lexical_cast<int>(parts[MinutePart]),
            boost::lexical_cast<int>(parts[SecondPart]));
        result.validate();
        return result;
    }

    //----------------------------------------------------------------
    std::list<HistoricalDate> DateTimeHelpers::createDateRange(const HistoricalDate & firstDay, const HistoricalDate & lastDay)
    {
        std::list<HistoricalDate> range;
        boost::gregorian::date date = firstDay.getAsGregorianDate();
        boost::gregorian::date endDate = lastDay.getAsGregorianDate();
        CHECK(endDate >= date, "Invalid date range");
        do
        {
            range.push_back(HistoricalDate(date.year(), date.month(), date.day()));
            date += boost::gregorian::date_duration(1);
        } while (date <= endDate);
        return range;
    }

    //----------------------------------------------------------------
    HistoricalDate DateTimeHelpers::getCurrentDate()
    {
        boost::gregorian::date today = boost::gregorian::day_clock::local_day();
        return HistoricalDate(today.year(), today.month(), today.day());
    }
};