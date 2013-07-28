#pragma once
#include <list>
#include <boost/signals2/mutex.hpp>
#include "Configuration/Configuration.hxx"
#include "Jobs/JobParameters.hxx"

namespace FeedHistoryDownloader
{
    /// Jobs to do. This class is thread-safe.
    class JobPool
    {
    public:
        /// Setup jobs pool.
        /// @param config Configuration to setup job pool from
        void setup(Configuration & config);

        /// Obtain next job parameters and pop it from the list.
        JobParameters popNextJob();

        /// Check whether the job pool is empty.
        bool done();
    private:
        static const std::string createDestFilename(const HistoricalDate & date, Configuration & configuration);

        std::list<JobParameters> m_jobsToDo;
        boost::signals2::mutex m_mutex;
    };
}