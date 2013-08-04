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
        const std::list<HistoricalDate> & getDatesToRequest();

        /// Get API key.
        const std::string & getApiKey();

        /// Get output dir.
        const std::string & getOutputDir();

        /// Get feed id.
        int getFeedId();

        /// Get max threads.
        int getMaxThreads();

        /// Get profile name.
        const std::string & getProfileName();
    private:
        Configuration(Configuration & configuration);
 
        std::list<HistoricalDate> m_datesToRequest;
        std::string m_apiKey;
        std::string m_outputDir;
        std::string m_profileName;
        int m_feedId;
        int m_maxThreads;
        boost::signals2::mutex m_mutex;
    };
}