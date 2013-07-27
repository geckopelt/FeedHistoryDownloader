#include <curl/curl.h>
#include "Helpers/Guards.hxx"
#include "Helpers/HttpHelper.hxx"

namespace FeedHistoryDownloader
{
	class HttpHelper::Implementation
	{
	public:
		//----------------------------------------------------------------
		Implementation() : m_curl(curl_easy_init())
		{
		}

		//----------------------------------------------------------------
		void setup(const std::string & hostname, const UrlArgs & args)
		{
			CHECK(CURLE_OK == curl_easy_setopt(m_curl, CURLOPT_URL, (hostname + args.getArgs()).c_str()), "Can't set URL");
			CHECK(CURLE_OK == curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1L), "Can't enable CURL redirects");
		}

		//----------------------------------------------------------------
		const std::string perform() const
		{
			CURLcode res = curl_easy_perform(m_curl);
			CHECK(CURLE_OK == res, std::string(curl_easy_strerror(res)));
			return ""; // $TMP
		}

		//----------------------------------------------------------------
		virtual ~Implementation()
		{
			if (NULL != m_curl)
			{
				curl_easy_cleanup(m_curl);
			}
		}

	private:
		CURL * m_curl;
	};

	//----------------------------------------------------------------
	HttpHelper::HttpHelper()
	{
		m_implementation = new Implementation();
	}

	//----------------------------------------------------------------
	HttpHelper::~HttpHelper()
	{
		if (NULL != m_implementation)
		{
			delete m_implementation;
		}
	}

	//----------------------------------------------------------------
	const std::string HttpHelper::performGet(const std::string & hostname, const UrlArgs & args) const
	{
		m_implementation->setup(hostname, args);
		return m_implementation->perform();
	}
}