#include "DataRetrievalJob.hxx"

namespace FeedHistoryDownloader
{
    //----------------------------------------------------------------
    DataRetrievalJob::DataRetrievalJob(IDataProvider * dataProvider) :
        m_dataProvider(dataProvider)
    {
    }

    //----------------------------------------------------------------
    DataRetrievalJob::DataRetrievalJob()
    {
    }

    //----------------------------------------------------------------
    DataRetrievalJob::~DataRetrievalJob()
    {
    }
}
