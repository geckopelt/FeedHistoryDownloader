#include <stdlib.h>
#include <iostream>
#include "DownloaderFacade.hxx"
#include "Guards.hxx"
#include <stdexcept>

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
        std::cout << "An error occured: \"" << exception.what() << "\"" << std::endl;
        return EXIT_FAILURE;
    }
    catch (...)
    {
        std::cout << "An unknown error occured" << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
