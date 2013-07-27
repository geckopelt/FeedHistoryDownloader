#pragma once
#include "DataProviders/IDataProvider.hxx"

namespace FeedHistoryDownloader
{
    /// Data retrieval job.
    class DataRetrievalJob
    {
    public:
        DataRetrievalJob(IDataProvider * dataProvider);
        virtual ~DataRetrievalJob();
		void operator() ();
    private:
        DataRetrievalJob();
        IDataProvider * m_dataProvider;
    };
}
