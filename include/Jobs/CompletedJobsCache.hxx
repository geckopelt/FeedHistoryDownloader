#pragma once
#include <string>
#include <set>
#include "DataProviders/HistoricalDate.hxx"

namespace FeedHistoryDownloader
{
    /// Completed jobs cache.
    class CompletedJobsCache
    {
    public:
        /// Cache job as completed
        /// @param date Job historical date
        void setJobCompleted(const HistoricalDate & date);

        /// Check whether job is already completed for this date.
        /// @param date Job historical date
        bool isJobAlreadyCompleted(const HistoricalDate & date) const;

        /// Save cache to file.
        /// @param filename Cache filename
        void save(const std::string & filename) const;

        /// Load cache from file.
        /// @param filename Cache filename
        void load(const std::string & filename);
    private:
        std::set<std::string> m_cache;
    };
}