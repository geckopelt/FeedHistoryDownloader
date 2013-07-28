#pragma once
#include <string>

namespace FeedHistoryDownloader
{
    /// A simple implementation of time for historical data retrieval purposes.
    class HistoricalTime
    {
    public:
        /// Ctor.
        /// @param hour Hour value
        /// @param minite Minute value
        /// @param second Second value
        HistoricalTime(int hour, int minute, int second);

        /// Get historical time value as string
        const std::string getAsString() const;

        /// Validate and throw an exception in case of any problems.
        void validate() const;

        virtual ~HistoricalTime();
    private:
        HistoricalTime();

        int m_hour;
        int m_minute;
        int m_second;
    };
}
