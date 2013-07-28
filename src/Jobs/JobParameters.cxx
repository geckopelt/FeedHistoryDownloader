#include "Jobs/JobParameters.hxx"

namespace FeedHistoryDownloader
{
    //----------------------------------------------------------------
    JobParameters::JobParameters(const HistoricalDate & date, const std::string & destFilename) : 
        m_date(date), m_destFilename(destFilename)
    {
    }

    //----------------------------------------------------------------
    const HistoricalDate & JobParameters::getDate() const
    {
        return m_date;
    }

    //----------------------------------------------------------------
    const std::string & JobParameters::getDestFilename() const
    {
        return m_destFilename;
    }
}