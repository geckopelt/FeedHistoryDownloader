#pragma once
#include <list>
#include <boost/signals2/mutex.hpp>
#include "Configuration/Configuration.hxx"
#include "Jobs/JobParameters.hxx"
#include "Jobs/CompletedJobsCache.hxx"

namespace FeedHistoryDownloader
{
    /// Jobs to do. This class is thread-safe.
    class JobPool
    {
    public:
        /// Setup jobs pool.
        /// @param config Configuration to setup job pool from
        void setup(Configuration & config);

        /// Obtain next job parameters and pop it from the list
        JobParameters popNextJob();

        /// Check whether the job pool is empty.
        bool done();

        /// Called on job failure.
        /// @param jobParameters Failed job parameters
        /// @param reason Error message
        void onJobFailure(const JobParameters & jobParameters, const std::string & reason);

        /// Called on generic worker failure.
        /// @param reason Error message
        void onWorkerFailure(const std::string & reason);

        /// Called on job completion.
        /// @param jobParameters Completed job parameters
        void onJobCompleted(const JobParameters & jobParameters);

        /// Called when all jobs are complete
        void onAllJobsCompleted();
    private:
        static const std::string createDestFilename(const HistoricalDate & date, Configuration & configuration);

        std::list<JobParameters> m_jobsToDo;
        boost::signals2::mutex m_mutex;
        CompletedJobsCache m_cache;
        std::string m_cacheFilename;
    };
}