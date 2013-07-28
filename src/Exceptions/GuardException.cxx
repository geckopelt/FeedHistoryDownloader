#include <string>
#include <boost/format.hpp>
#include "Exceptions/GuardException.hxx"

namespace FeedHistoryDownloader
{
    //----------------------------------------------------------------
    GuardException::GuardException(const std::string & message, const std::string & filename, size_t line) :
        ExceptionBase(message),
        m_filename(filename),
        m_line(line)
    {
        m_what = (boost::format("Guard violation at \"%s\" (%d): %s") % getFilename() % m_line % m_message).str();
    }

    //----------------------------------------------------------------
    GuardException::~GuardException() throw()
    {
    }

    //----------------------------------------------------------------
    const std::string & GuardException::getFilename() const
    {
        return m_filename;
    }

    const char * GuardException::what() const throw()
    {
        return m_what.c_str();
    }
}
