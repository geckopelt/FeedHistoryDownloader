#pragma once
#include "Helpers/HttpHelper.hxx"
#include "DataProviders/IDataProvider.hxx"

namespace FeedHistoryDownloader
{
    /// Xively Data provider
    class XivelyDataProvider: public IDataProvider
    {
    public:
        /// Ctor. 
        /// @param httpHelper HTTP helper wrapper to use
        /// @param feedId Xively feed id
        /// @param apiKey Xively API key
        XivelyDataProvider(IHttpHelper * httpHelper, int feedId, const std::string & apiKey);

        virtual ~XivelyDataProvider();

        /// @see IDataProvider
        const IDataProvider::HistoricalData getData(const HistoricalDate & date);
    private:
        XivelyDataProvider();

        const IDataProvider::HistoricalData parseXivelyResponse(const std::vector<char> & data);

        IHttpHelper * m_httpHelper;
        int m_feedId;
        std::string m_apiKey;
    };
}
