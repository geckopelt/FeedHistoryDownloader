#define _SCL_SECURE_NO_WARNINGS
#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
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
};