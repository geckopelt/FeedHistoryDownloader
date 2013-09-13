#pragma once
#include "Outputters/IOutputter.hxx"

namespace FeedHistoryDownloader
{
    /// CSV text file outputter
    class CsvOutputter : public IOutputter
    {
    public:
        /// @see IOutputter
        void output(const HistoricalDate & date, const std::vector<IDataProvider::DataPointType> & dataPoints);
    };
}