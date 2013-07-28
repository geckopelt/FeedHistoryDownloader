#pragma once
#include <string>
#include <boost/format.hpp>
#include "Helpers/Guards.hxx"
#include "DataProviders/HistoricalTime.hxx"

namespace FeedHistoryDownloader
{
    //----------------------------------------------------------------
    HistoricalTime::HistoricalTime(int hour, int minute, int second) :
        m_hour(hour), m_minute(minute), m_second(second)
    {
    }

    //----------------------------------------------------------------
    HistoricalTime::~HistoricalTime()
    {
    }

    //----------------------------------------------------------------
    const std::string HistoricalTime::getAsString() const
    {
        return (boost::format("%02d:%02d:%02d") % m_hour % m_minute % m_second).str();
    }

    //----------------------------------------------------------------
    void HistoricalTime::validate() const
    {
        CHECK(m_hour >= 0 && m_hour < 24, "Invalid hour value");
        CHECK(m_minute >= 0 && m_minute < 60, "Invalid minute value");
        CHECK(m_second >= 0 && m_second < 60, "Invalid second value");
    }
}
