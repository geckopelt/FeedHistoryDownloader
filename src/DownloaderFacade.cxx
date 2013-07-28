#include <list>
#include <boost/log/trivial.hpp>
#include <boost/thread/thread.hpp>
#include "Configuration/Configuration.hxx"
#include "Jobs/JobPool.hxx"
#include "Jobs/DataRetrievalWorker.hxx"
#include "DownloaderFacade.hxx"

namespace FeedHistoryDownloader
{
    //----------------------------------------------------------------
    void DownloaderFacade::downloadHistoricalData(const std::string & configFile)
    {
        JobPool jobPool;
        Configuration configuration;
        configuration.parse(configFile);
        jobPool.setup(configuration);

        const size_t MaxWorkers = 3; // TODO: make configurable
        std::list<DataRetrievalWorker> workers;
        for (size_t i = 0; i < MaxWorkers; i++)
        {
            workers.push_back(DataRetrievalWorker(jobPool, configuration));
        }

        std::list<boost::thread> threads;
        for (std::list<DataRetrievalWorker>::iterator it = workers.begin(); it != workers.end(); it++)
        {
            threads.push_back(boost::thread(*it));
        }

        // Wait for all threads
        for (std::list<boost::thread>::iterator it = threads.begin(); it != threads.end(); it++)
        {
            it->join();
        }
        BOOST_LOG_TRIVIAL(trace) << "Done!";
    }
}
