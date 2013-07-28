#pragma once
#include <Helpers/IHttpHelper.hxx>

namespace FeedHistoryDownloader
{
    /// HTTP communication helper implementation. 
    /// No proxy support, non-thread safe.
    class HttpHelper : public IHttpHelper
	{
	public:
		HttpHelper();

		virtual ~HttpHelper();

        /// @see IHttpHelper
        const std::vector<char> performGet(const std::string & urlBase, const UrlArgs & args, const std::map<std::string, std::string> & headers) const;

		/// @see IHttpHelper
		const std::vector<char> performGet(const std::string & urlBase, const UrlArgs & args) const;

	private:
		class Implementation;
		Implementation * m_implementation;
	};
}
