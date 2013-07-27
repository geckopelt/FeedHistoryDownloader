#include <stdexcept>
#include <stdlib.h>
#include <boost/log/trivial.hpp>
#include "DownloaderFacade.hxx"
#include "Guards.hxx"

using namespace FeedHistoryDownloader;

//----------------------------------------------------------------
int main(int argc, char* argv[])
{
    try
    {
        DownloaderFacade downloader;

        CHECK(false, "ololo");
    }
    catch (const std::exception & exception)
    {
		BOOST_LOG_TRIVIAL(fatal) << "An error occured: \"" << exception.what() << "\"";
        return EXIT_FAILURE;
    }
    catch (...)
    {
		BOOST_LOG_TRIVIAL(fatal) << "An unknown error occured";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
