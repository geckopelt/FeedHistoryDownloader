#pragma once
#include <vector>
#include "DataProviders/HistoricalDate.hxx"
#include "DataProviders/DataPoint.hxx"

namespace FeedHistoryDownloader
{
    /// Historical data provider interface.
    struct IDataProvider
    {
        /// Datapoint value type.
        typedef float DataPointValueType;

        /// Datapoint type.
        typedef DataPoint<DataPointValueType> DataPointType;

        /// Historical data list
        typedef std::vector<DataPointType> HistoricalData;

        /// Retrieve historical data.
        /// @param date Date to retrieve data for.
        /// @return A list of datapoints.
        virtual const HistoricalData getData(const HistoricalDate & date) = 0;

        virtual ~IDataProvider() {}
    };
}
