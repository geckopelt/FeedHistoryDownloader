#include <exception>
#include "Exceptions/ExceptionBase.hxx"

namespace FeedHistoryDownloader
{
    //----------------------------------------------------------------
    ExceptionBase::ExceptionBase(const std::string & message) : std::exception(), m_message(message)
    {
    }

    //----------------------------------------------------------------
    ExceptionBase::~ExceptionBase() throw()
    {
    }

    //----------------------------------------------------------------
    const char * ExceptionBase::what() const throw()
    {
        return m_message.c_str();
    }
}

