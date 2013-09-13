#pragma once
#include <vector>
#include "DataProviders/IDataProvider.hxx"

namespace FeedHistoryDownloader
{
    /// Historical data outputter interface
    struct IOutputter
    {
        /// Output historical data
        /// @param date Date
        /// @param dataPoints A list of data points
        virtual void output(const HistoricalDate & date, const std::vector<IDataProvider::DataPointType> & dataPoints) = 0;

        virtual ~IOutputter() {}
    };
}