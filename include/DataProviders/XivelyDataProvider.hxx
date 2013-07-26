#pragma once
#include "DataProviders/IDataProvider.hxx"

namespace FeedHistoryDownloader
{
    /// Xively Data provider
    class XivelyDataProvider: public IDataProvider
    {
        XivelyDataProvider();
        virtual ~XivelyDataProvider();
    };
}
