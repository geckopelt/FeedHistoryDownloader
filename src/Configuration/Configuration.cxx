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

        m_datesToRequest.clear();
        std::vector<std::string> datesToRequest;
        boost::split(datesToRequest, props.get<std::string>(SectionName + "DatesToRequest"), boost::is_any_of(", "), boost::algorithm::token_compress_on);
        for (std::vector<std::string>::const_iterator it = datesToRequest.begin(); it != datesToRequest.end(); it++)
        {
            m_datesToRequest.push_back(DateTimeHelpers::parseDate(*it));
        }

        m_apiKey = props.get<std::string>(SectionName + "ApiKey");
        m_outputDir = props.get<std::string>(SectionName + "OutputDir");
        m_feedId = props.get<int>(SectionName + "FeedId");
    }

    //----------------------------------------------------------------
    const std::list<HistoricalDate> & Configuration::getDatesToRequest()
    {
        boost::lock_guard<boost::signals2::mutex> lock(m_mutex);
        return m_datesToRequest;
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
}