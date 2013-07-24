#include <stdlib.h>
#include <iostream>
#include "DownloaderFacade.hxx"

int main(int argc, char* argv[])
{
    try
    {
        FeedHistoryDownloader::DownloaderFacade downloader;
    }
    catch (std::exception & exception)
    {
        std::cout << "An error occured: \"" << exception.what() << "\"" << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
