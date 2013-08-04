#define _SCL_SECURE_NO_WARNINGS
#include <vector>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/thread/lock_guard.hpp>
#include "Helpers/DateTimeHelpers.hxx"
#include "Configuration/Configuration.hxx"

namespace FeedHistoryDownloader
{
    //----------------------------------------------------------------
    Configuration::Configuration() : m_feedId(0)
    {
    }

    //----------------------------------------------------------------
    void Configuration::parse(const std::string & filename)
    {
        boost::lock_guard<boost::signals2::mutex> lock(m_mutex);
        const std::string SectionName = "FeedHistoryDownloader.";

        boost::property_tree::ptree props;
        boost::property_tree::ini_parser::read_ini(filename, props);

        m_apiKey = props.get<std::string>(SectionName + "ApiKey");
        m_outputDir = props.get<std::string>(SectionName + "OutputDir");
        m_feedId = props.get<int>(SectionName + "FeedId");
        m_profileName = props.get<std::string>(SectionName + "ProfileName");
        m_startDate = DateTimeHelpers::parseDate(props.get<std::string>(SectionName + "StartDate"));
        m_maxThreads = props.get<size_t>(SectionName + "MaxThreads");
    }

    //----------------------------------------------------------------
    const std::list<HistoricalDate> Configuration::getDatesToRequest()
    {
        boost::lock_guard<boost::signals2::mutex> lock(m_mutex);
        return DateTimeHelpers::createDateRange(m_startDate, DateTimeHelpers::getCurrentDate());
    }

    //----------------------------------------------------------------
    const std::string & Configuration::getApiKey()
    {
        boost::lock_guard<boost::signals2::mutex> lock(m_mutex);
        return m_apiKey;
    }

    //----------------------------------------------------------------
    const std::string & Configuration::getOutputDir()
    {
        boost::lock_guard<boost::signals2::mutex> lock(m_mutex);
        return m_outputDir;
    }

    //----------------------------------------------------------------
    int Configuration::getFeedId()
    {
        boost::lock_guard<boost::signals2::mutex> lock(m_mutex);
        return m_feedId;
    }

    //----------------------------------------------------------------
    const std::string & Configuration::getProfileName()
    {
        boost::lock_guard<boost::signals2::mutex> lock(m_mutex);
        return m_profileName;
    }

    //----------------------------------------------------------------
    const HistoricalDate & Configuration::getStartDate()
    {
        boost::lock_guard<boost::signals2::mutex> lock(m_mutex);
        return m_startDate;
    }

    //----------------------------------------------------------------
    size_t Configuration::getMaxThreads()
    {
        boost::lock_guard<boost::signals2::mutex> lock(m_mutex);
        return m_maxThreads;
    }
}