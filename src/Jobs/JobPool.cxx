#include <boost/thread/lock_guard.hpp>
#include <boost/log/trivial.hpp>
#include "Helpers/Guards.hxx"
#include "Jobs/JobPool.hxx"

namespace FeedHistoryDownloader
{
    //----------------------------------------------------------------
    void JobPool::setup(Configuration & config)
    {
        boost::lock_guard<boost::signals2::mutex> lock(m_mutex);

        const std::string CacheExtension = ".cache";
        m_cacheFilename = config.getProfileName() + CacheExtension; 
        m_cache.load(m_cacheFilename);

        const std::list<HistoricalDate> dates = config.getDatesToRequest();
        BOOST_LOG_TRIVIAL(trace) << dates.size() << " date(s) in range";

        for (std::list<HistoricalDate>::const_iterator it = dates.begin(); it != dates.end(); it++)
        {
            if (!m_cache.isJobAlreadyCompleted(*it))
            {
                m_jobsToDo.push_back(JobParameters(*it, createDestFilename(*it, config)));
            }
        }
        BOOST_LOG_TRIVIAL(trace) << m_jobsToDo.size() << " jobs to process";
    }
   
    //----------------------------------------------------------------
    JobParameters JobPool::popNextJob()
    {
        boost::lock_guard<boost::signals2::mutex> lock(m_mutex);
        CHECK(!m_jobsToDo.empty(), "No more jobs");
        JobParameters params = m_jobsToDo.front();
        m_jobsToDo.pop_front();
        return params;
    }

    //----------------------------------------------------------------
    bool JobPool::done()
    {
        boost::lock_guard<boost::signals2::mutex> lock(m_mutex);
        return m_jobsToDo.empty();
    }

    //----------------------------------------------------------------
    void JobPool::onJobFailure(const JobParameters & jobParameters, const std::string & reason)
    {
        boost::lock_guard<boost::signals2::mutex> lock(m_mutex);
        BOOST_LOG_TRIVIAL(error) << "Can't retrieve data for " << jobParameters.getDate().getAsString() << "reason: " << reason;
    }

    //----------------------------------------------------------------
    void JobPool::onWorkerFailure(const std::string & reason)
    {
        // Worker failure is fatal
        boost::lock_guard<boost::signals2::mutex> lock(m_mutex);
        BOOST_LOG_TRIVIAL(fatal) << reason;
        throw ExceptionBase(reason);
    }

    //----------------------------------------------------------------
    void JobPool::onJobCompleted(const JobParameters & jobParameters)
    {
        boost::lock_guard<boost::signals2::mutex> lock(m_mutex);
        m_cache.setJobCompleted(jobParameters.getDate());
    }

    //----------------------------------------------------------------
    void JobPool::onAllJobsCompleted()
    {
        m_cache.save(m_cacheFilename);
    }

    //----------------------------------------------------------------
    const std::string JobPool::createDestFilename(const HistoricalDate & date, Configuration & configuration) 
    {
        return configuration.getOutputDir() + "/" + date.getAsString() + ".txt";
    }
}