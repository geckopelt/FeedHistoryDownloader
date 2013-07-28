#pragma once
#include "DataProviders/HistoricalDate.hxx"

namespace FeedHistoryDownloader
{
    /// Data retrieval job parameters.
    class JobParameters
    {
    public:
        /// Ctor.
        /// @param date Date to retrieve data for.
        JobParameters(const HistoricalDate & date, const std::string & destFilename);

        /// Get historical date to retrieve data for
        const HistoricalDate & getDate() const;

        /// Get destination filename for this job
        const std::string & getDestFilename() const;
    private:
        HistoricalDate m_date;
        std::string m_destFilename;
    };
}
