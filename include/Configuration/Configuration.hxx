#pragma once
#include <list>
#include <string>
#include <boost/signals2/mutex.hpp>
#include "DataProviders/HistoricalDate.hxx"

namespace FeedHistoryDownloader
{
    /// Feed history downloader configuration. This class is thread-safe.
    class Configuration
    {
    public:
        Configuration();

        /// Parse history downloader configuration.
        /// @param filename FHD configuration file
        void parse(const std::string & filename);

        /// Get historical dates to process.
        const std::list<HistoricalDate> getDatesToRequest();

        /// Get API key.
        const std::string & getApiKey();

        /// Get output dir.
        const std::string & getOutputDir();

        /// Get feed id.
        int getFeedId();

        /// Get max threads.
        size_t getMaxThreads();

        /// Get profile name.
        const std::string & getProfileName();

        /// Get start date.
        const HistoricalDate & getStartDate();
    private:
        Configuration(Configuration & configuration);
 
        std::string m_apiKey;
        std::string m_outputDir;
        std::string m_profileName;
        int m_feedId;
        size_t m_maxThreads;
        HistoricalDate m_startDate;

        boost::signals2::mutex m_mutex;
    };
}