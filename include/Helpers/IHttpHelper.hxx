#pragma once

#include <string>
#include <Helpers/UrlArgs.hxx>

namespace FeedHistoryDownloader
{
    /// HTTP communication helper interface.
    struct IHttpHelper
	{
		/// Perform HTTP GET request and get results
		/// @param hostname Server to query
		/// @param args URL args
		/// @return Server response text
		virtual const std::string performGet(const std::string & hostname, const UrlArgs & args) const = 0;

		virtual ~IHttpHelper() {}
	};
}
