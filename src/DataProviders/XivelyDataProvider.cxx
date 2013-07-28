#define _SCL_SECURE_NO_WARNINGS
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include "Helpers/Guards.hxx"
#include "DataProviders/XivelyDataProvider.hxx"
#include "Helpers/DateTimeHelpers.hxx"

namespace FeedHistoryDownloader
{
    //----------------------------------------------------------------
    XivelyDataProvider::XivelyDataProvider(IHttpHelper * httpHelper, int feedId, const std::string & apiKey) : 
        m_httpHelper(httpHelper),
        m_feedId(feedId),
        m_apiKey(apiKey)
    {
    }

    //----------------------------------------------------------------
    XivelyDataProvider::~XivelyDataProvider()
    {
    }

    //----------------------------------------------------------------
    const IDataProvider::HistoricalData XivelyDataProvider::getData(const HistoricalDate & date)
    {
        // This code is experimental
        const std::string XivelyEndpoint = "http://api.xively.com/v2/feeds/";
        const std::string Format = ".csv";

        std::string baseUrl = XivelyEndpoint + (boost::format("%d") % m_feedId).str() + Format;

        UrlArgs args;
        args.addArg("start", date.getAsString());
        args.addArg("duration", "24hours");
        args.addArg("interval", "900"); // Every 15 minutes

        std::map<std::string, std::string> headers;
        headers["X-ApiKey"] = m_apiKey;

        return parseXivelyResponse(m_httpHelper->performGet(baseUrl, args, headers));
    }

    //----------------------------------------------------------------
    const IDataProvider::HistoricalData XivelyDataProvider::parseXivelyResponse(const std::vector<char> & data)
    {
        // Xively API returns ASCII text
        std::string serverResponse(data.begin(), data.end());

        std::vector<std::string> lines;
        boost::split(lines, serverResponse, boost::is_any_of("\r\n"));

        // TODO: currently we're dealing with single-value feed only. 
        // This needs to be improved in future, though is absolutely ok for current purposes.
        
        const int PartsExpected = 4;
        const int DatePart = 1;
        const int TimePart = 2;
        const int ValuePart = 3;

        IDataProvider::HistoricalData result;
        for (std::vector<std::string>::const_iterator it = lines.begin(); it != lines.end(); it++)
        {
            std::vector<std::string> parts;
            boost::split(parts, *it, boost::is_any_of(",TZ"), boost::algorithm::token_compress_on);

            CHECK(PartsExpected == parts.size(), "Invalid historical line response: " + (*it));
   
            result.push_back(IDataProvider::DataPointType(
                boost::lexical_cast<IDataProvider::DataPointValueType>(parts[ValuePart]),
                DateTimeHelpers::parseDate(parts[DatePart]),
                DateTimeHelpers::parseTime(parts[TimePart])));
        }
        return result;
    }
}
