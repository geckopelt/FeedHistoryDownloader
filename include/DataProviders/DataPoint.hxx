#pragma once
#include "DataProviders/HistoricalDate.hxx"
#include "DataProviders/HistoricalTime.hxx"

namespace FeedHistoryDownloader
{
    /// Datapoint template. Though only double-datapoints are used, this template will be useful in future.
    template <typename DataType> class DataPoint
    {
    public:
        /// @param value Data value
        /// @param date Datapoint's historical date
        /// @param time Datapoint's historical time
        DataPoint(DataType value, const HistoricalDate & date, const HistoricalTime & time) :
            m_value(value), m_date(date), m_time(time)
        {
        }

        /// Get datapoint value.
        const DataType & getValue() const
        {
            return m_value;
        }

        /// Get datapoint date.
        const HistoricalDate & getDate() const
        {
            return m_date;
        }

        /// Get datapoint time.
        const HistoricalTime & getTime() const
        {
            return m_time;
        }

    private:
        DataType m_value;
        HistoricalDate m_date;
        HistoricalTime m_time;
    };
}