#pragma once
#include <string>
#include <map>
#include <fstream>
#include <boost/filesystem.hpp>
#include "Helpers/Guards.hxx"
#include "Jobs/CompletedJobsCache.hxx"

namespace FeedHistoryDownloader
{
    //----------------------------------------------------------------
    void CompletedJobsCache::setJobCompleted(const HistoricalDate & date)
    {
        // Keep it simple, stupid
        m_cache.insert(date.getAsString());
    }

    //----------------------------------------------------------------
    bool CompletedJobsCache::isJobAlreadyCompleted(const HistoricalDate & date) const
    {
        return m_cache.find(date.getAsString()) != m_cache.end();
    }

    //----------------------------------------------------------------
    void CompletedJobsCache::save(const std::string & filename) const
    {
        std::ofstream cacheFile(filename);
        CHECK(cacheFile.is_open(), "Can't open \"" + filename + "\" for writing");
        for (std::set<std::string>::const_iterator it = m_cache.begin(); it != m_cache.end(); it++)
        {
            cacheFile << (*it) << std::endl;
        }
    }

    //----------------------------------------------------------------
    void CompletedJobsCache::load(const std::string & filename)
    {
        if (!boost::filesystem::exists(filename))
            return;

        m_cache.clear();
        std::ifstream cacheFile(filename);
        CHECK(cacheFile.is_open(), "Can't open \"" + filename + "\" for reading");
        while (cacheFile.good())
        {
            std::string date;
            cacheFile >> date;
            m_cache.insert(date);
        }
    }
}