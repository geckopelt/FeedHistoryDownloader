#include <fstream>
#include "Helpers/Guards.hxx"
#include "Outputters/CsvOutputter.hxx"

namespace FeedHistoryDownloader
{
    // TODO: use configuration

    //----------------------------------------------------------------
    void CsvOutputter::output(const HistoricalDate & date, const std::vector<IDataProvider::DataPointType> & dataPoints)
    {
        const std::string filename = date.getAsString() + ".csv";

        std::ofstream s(filename);
        CHECK(s.is_open(), "Can't open " + filename);
        for (std::vector<IDataProvider::DataPointType>::const_iterator it = dataPoints.begin(); it != dataPoints.end(); it++)
        {
            s << it->getDate().getAsString() << " " << it->getTime().getAsString() << "," << it->getValue() << std::endl;
        }
    }
}