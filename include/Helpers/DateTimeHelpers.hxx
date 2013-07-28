#pragma once
#include <DataProviders/HistoricalDate.hxx>
#include <DataProviders/HistoricalTime.hxx>

namespace FeedHistoryDownloader
{
    /// Historical date/time parser helpers. 
    class DateTimeHelpers
	{
	public:
        /// Parse historical date string.
        /// @param date Historical date in "YYYY-MM-DD" format
        /// @return HistoricalDate ready for use
        static HistoricalDate parseDate(const std::string & date);

        /// Parse historical date string.
        /// @param date Historical date in "HH:MM:SS[.ms]" format
        /// @return HistoricalTime ready for use
        static HistoricalTime parseTime(const std::string & time);
	};
}
