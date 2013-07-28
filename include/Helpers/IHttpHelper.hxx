#pragma once

#include <vector>
#include <map>
#include <Helpers/UrlArgs.hxx>

namespace FeedHistoryDownloader
{
    /// HTTP communication helper interface.
    struct IHttpHelper
	{
		/// Perform HTTP GET request and get results, using custom headers.
		/// @param urlBase URL base
		/// @param args URL args
        /// @param Custom HTTP Headers
		/// @return Server response bytes
		virtual const std::vector<char> performGet(const std::string & urlBase, const UrlArgs & args, const std::map<std::string, std::string> & headers) const = 0;

	    /// Perform HTTP GET request and get results.
		/// @param urlBase URL base
		/// @param args URL args
        /// @param Custom HTTP Headers
		/// @return Server response bytes        
        virtual const std::vector<char> performGet(const std::string & urlBase, const UrlArgs & args) const = 0;

		virtual ~IHttpHelper() {}
	};
}
