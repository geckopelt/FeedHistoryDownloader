#pragma once
#include <string>

namespace FeedHistoryDownloader
{
    /// All the stuff together.
    class DownloaderFacade
    {
    public:
        /// Download all the historical data.
        /// @param configFile Configuration file to use
        void downloadHistoricalData(const std::string & configFile);
    };
}
