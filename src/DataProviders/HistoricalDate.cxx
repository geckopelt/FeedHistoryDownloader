#include <boost/format.hpp>
#include "Helpers/Guards.hxx"
#include "DataProviders/HistoricalDate.hxx"

namespace FeedHistoryDownloader
{
    //----------------------------------------------------------------
    HistoricalDate::HistoricalDate(int year, int month, int day) :
        m_year(year), m_month(month), m_day(day)
    {
    }

    //----------------------------------------------------------------
    HistoricalDate::~HistoricalDate()
    {
    }

    //----------------------------------------------------------------
    const std::string HistoricalDate::getAsString() const
    {
        return (boost::format("%04d-%02d-%02d") % m_year % m_month % m_day).str();
    }

    //----------------------------------------------------------------
    void HistoricalDate::validate() const
    {
        CHECK(m_month >= 1 && m_month <= 12, "Invalid month value");
        CHECK(m_day >= 1 && m_day <= 31, "Invalid day of month value");
    }
}
