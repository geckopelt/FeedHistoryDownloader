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

        /// Create date range.
        /// @param firstDay First day of a range
        /// @param lastDay Last day of a range
        /// @return Historical date range
        static std::list<HistoricalDate> createDateRange(const HistoricalDate & firstDay, const HistoricalDate & lastDay);

        /// Get current date
        /// @return Current HistoricalDate
        static HistoricalDate getCurrentDate();
	};
}
