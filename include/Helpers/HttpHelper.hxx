#pragma once

#include <string>
#include <Helpers/IHttpHelper.hxx>

namespace FeedHistoryDownloader
{
    /// HTTP communication helper implementation. This class is not thread-safe.
    class HttpHelper : public IHttpHelper
	{
	public:
		HttpHelper();

		virtual ~HttpHelper();

		/// @see IHttpHelper
		const std::string performGet(const std::string & hostname, const UrlArgs & args) const;

	private:
		class Implementation;
		Implementation * m_implementation;
	};
}
