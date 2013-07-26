#include "Exceptions/GuardException.hxx"

namespace FeedHistoryDownloader
{
    //----------------------------------------------------------------
    GuardException::GuardException(const std::string & message, const std::string & filename) :
        ExceptionBase(message),
        m_filename(filename)
    {
        m_what = std::string("Guard violation at \"") + getFilename() + "\", " + m_message;
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
