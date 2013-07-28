#include <vector>
#include <curl/curl.h>
#include <boost/format.hpp>
#include "Helpers/Guards.hxx"
#include "Helpers/HttpHelper.hxx"

namespace FeedHistoryDownloader
{
    namespace
    {
        /// HTTP Headers list wrapper
        class HttpHeaders
        {
        public:
            //----------------------------------------------------------------
            HttpHeaders() : m_list(NULL)
            {
            }

            //----------------------------------------------------------------
            void append(const std::string & key, const std::string & value)
            {
                m_list = curl_slist_append(m_list, (key + ":" + value).c_str());
            }

            //----------------------------------------------------------------
            curl_slist * getList()
            {
                return m_list;
            }

            //----------------------------------------------------------------
            virtual ~HttpHeaders()
            {
                if (NULL != m_list)
                {
                    curl_slist_free_all(m_list);
                }
            }

        private:
            struct curl_slist * m_list;
        };
    }

    //----------------------------------------------------------------
    size_t curlWriteFunction(char * ptr, size_t size, size_t nmemb, void * userdata)
    {
        std::vector<char> * data = static_cast<std::vector<char>*>(userdata);
        const size_t bytesCount = size * nmemb;
        std::vector<char> buffer(bytesCount);
        memcpy(&buffer[0], ptr, bytesCount);
        data->insert(data->end(), buffer.begin(), buffer.end());
        return bytesCount;
    }

   	class HttpHelper::Implementation
	{
	public:
        friend size_t curlWriteFunction(char * ptr, size_t size, size_t nmemb, void * userdata);
		//----------------------------------------------------------------
		Implementation() : m_curl(curl_easy_init())
		{
		}

		//----------------------------------------------------------------
		void setup(const std::string & urlBase, const UrlArgs & args)
		{
			CHECK(CURLE_OK == curl_easy_setopt(m_curl, CURLOPT_URL, (urlBase + args.getArgs()).c_str()), "Can't set URL");
			CHECK(CURLE_OK == curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1L), "Can't enable curl redirects");
            CHECK(CURLE_OK == curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, curlWriteFunction), "Can't set curl write function");
        }

        //----------------------------------------------------------------
        void setupCustomHeaders(struct curl_slist * headersList)
        {
            CHECK(CURLE_OK == curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, headersList), "Can't set curl HTTP custom headers");
        }

 		//----------------------------------------------------------------
		const std::vector<char> perform() const
		{
            const long HttpOk = 200;
            std::vector<char> data;
            CHECK(CURLE_OK == curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &data), "Can't set curl writedata");
			CURLcode res = curl_easy_perform(m_curl);
			CHECK(CURLE_OK == res, std::string(curl_easy_strerror(res)));
            long responseCode(0);
            res = curl_easy_getinfo(m_curl, CURLINFO_RESPONSE_CODE, &responseCode);
            CHECK(HttpOk == responseCode, (boost::format("Bad HTTP response code: %d") % responseCode).str());
			return data;
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
    const std::vector<char> HttpHelper::performGet(const std::string & urlBase, const UrlArgs & args, const std::map<std::string, std::string> & headers) const
    {
	    m_implementation->setup(urlBase, args);
        HttpHeaders customHeaders;
        for (std::map<std::string, std::string>::const_iterator it = headers.begin(); it != headers.end(); it++)
        {
            customHeaders.append(it->first, it->second);
        }
        m_implementation->setupCustomHeaders(customHeaders.getList());
		return m_implementation->perform();
    }

	//----------------------------------------------------------------
	const std::vector<char> HttpHelper::performGet(const std::string & urlBase, const UrlArgs & args) const
	{
		m_implementation->setup(urlBase, args);
        m_implementation->setupCustomHeaders(NULL);
		return m_implementation->perform();
	}
}