#pragma once
#include <string>

namespace FeedHistoryDownloader
{
    /// A simple implementation of calendar date for historical data retrieval purposes.
    class HistoricalDate
    {
    public:
        /// Ctor.
        /// @param Year
        /// @param Month, starts with 1
        /// @param Day of month, starts with 1
        HistoricalDate(int year, int month, int day);

        /// Get historical date value as string
        const std::string getAsString() const;

        /// Validate and throw an exception in case of any problems.
        void validate() const;

        virtual ~HistoricalDate();
    private:
        HistoricalDate();

        int m_year;
        int m_month;
        int m_day;
    };
}
