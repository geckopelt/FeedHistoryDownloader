#include <memory>
#include <boost/log/trivial.hpp>
#include "Helpers/IHttpHelper.hxx"
#include "DataProviders/XivelyDataProvider.hxx"
#include "Jobs/DataRetrievalWorker.hxx"

// TMP
#include "Outputters/CsvOutputter.hxx"

namespace FeedHistoryDownloader
{
    int DataRetrievalWorker::m_workerCount = 0;

    //----------------------------------------------------------------
    DataRetrievalWorker::DataRetrievalWorker(JobPool & jobPool, Configuration & configuration) : 
        m_jobPool(jobPool),
        m_configuration(configuration),
        m_workerId(m_workerCount)
    {
        m_workerCount++;
    }

    //----------------------------------------------------------------
    void DataRetrievalWorker::operator() ()
    {
        try
        {
            BOOST_LOG_TRIVIAL(trace) << m_workerId << ": Starting worker";

            std::auto_ptr<IHttpHelper> httpHelper(new HttpHelper());
            std::auto_ptr<IDataProvider> dataProvider(
                new XivelyDataProvider(
                    httpHelper.get(), 
                    m_configuration.getFeedId(), 
                    m_configuration.getApiKey()));

            // TMP
            CsvOutputter outputter;

            while (!m_jobPool.done())
            {
                JobParameters parameters = m_jobPool.popNextJob();
                try
                {
                    BOOST_LOG_TRIVIAL(trace) << m_workerId << ": Retrieving historical data for " << parameters.getDate().getAsString();
                    IDataProvider::HistoricalData data = dataProvider.get()->getData(parameters.getDate());

                    // TODO: stub
                    BOOST_LOG_TRIVIAL(trace) << m_workerId << ": Retrieved " << data.size() << " datapoints";
                    outputter.output(parameters.getDate(), data);

                    m_jobPool.onJobCompleted(parameters);
                }
                catch (const std::exception & ex)
                {
                    m_jobPool.onJobFailure(parameters, ex.what());
                }
            }
        }
        catch (const std::exception & exception)
        {
            m_jobPool.onWorkerFailure(exception.what());
        }
    }
}