#include <boost/thread/lock_guard.hpp>
#include "Helpers/Guards.hxx"
#include "Jobs/JobPool.hxx"

namespace FeedHistoryDownloader
{
    //----------------------------------------------------------------
    void JobPool::setup(Configuration & config)
    {
        boost::lock_guard<boost::signals2::mutex> lock(m_mutex);
        const std::list<HistoricalDate> & dates = config.getDatesToRequest();
        for (std::list<HistoricalDate>::const_iterator it = dates.begin(); it != dates.end(); it++)
        {
            m_jobsToDo.push_back(JobParameters(*it, createDestFilename(*it, config)));
        }
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
    const std::string JobPool::createDestFilename(const HistoricalDate & date, Configuration & configuration) 
    {
        return configuration.getOutputDir() + "/" + date.getAsString() + ".txt";
    }
}