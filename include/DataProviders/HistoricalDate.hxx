#pragma once
#include <string>
#include <boost/date_time/gregorian/gregorian_types.hpp>

namespace FeedHistoryDownloader
{
    /// A simple implementation of calendar date for historical data retrieval purposes.
    class HistoricalDate
    {
    public:
        // Default ctor. Sets everything to zero.
        HistoricalDate();

        /// Ctor.
        /// @param Year
        /// @param Month, starts with 1
        /// @param Day of month, starts with 1
        HistoricalDate(int year, int month, int day);

        /// Get historical date value as string
        const std::string getAsString() const;

        /// Get historical date value as boost gregorian date
        const boost::gregorian::date getAsGregorianDate() const;

        /// Validate and throw an exception in case of any problems.
        void validate() const;

        virtual ~HistoricalDate();
    private:
        int m_year;
        int m_month;
        int m_day;
    };
}
