#pragma once
#include "Jobs/JobPool.hxx"
#include "Configuration/Configuration.hxx"

namespace FeedHistoryDownloader
{
    /// Historical data retrieval worker.
    class DataRetrievalWorker
    {
    public:
        /// Ctor.
        DataRetrievalWorker(JobPool & jobPool, Configuration & configuration);

        /// Performs data retrieval.
        /// @param jobPool Job pool to query
        /// @param configuration Configuration to use
        void operator() ();

    private:
        JobPool & m_jobPool;
        Configuration & m_configuration;
        int m_workerId;
        static int m_workerCount;
    };
}