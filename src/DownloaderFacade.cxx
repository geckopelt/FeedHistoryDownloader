#include <iostream>
#include <boost/thread/thread.hpp>
#include "DownloaderFacade.hxx"
#include "DataRetrievalJob.hxx"

namespace FeedHistoryDownloader
{
    //----------------------------------------------------------------
    DownloaderFacade::DownloaderFacade()
    {
        std::cout << "Dummy!" << std::endl;

		boost::thread t1(boost::ref(DataRetrievalJob(NULL)));
		boost::thread t2(boost::ref(DataRetrievalJob(NULL)));
		boost::thread t3(boost::ref(DataRetrievalJob(NULL)));


    }
}
