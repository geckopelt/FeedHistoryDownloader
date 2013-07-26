#pragma once
#include "DataProviders/IDataProvider.hxx"

namespace FeedHistoryDownloader
{
    /// Data retrieval job.
    class DataRetrievalJob
    {
    public:
        /// Ctor.
        /// @param dataProvider DataProvider to use.
        DataRetrievalJob(IDataProvider * dataProvider);

        virtual ~DataRetrievalJob();

    private:
        DataRetrievalJob();

        IDataProvider * m_dataProvider;
    };
}
