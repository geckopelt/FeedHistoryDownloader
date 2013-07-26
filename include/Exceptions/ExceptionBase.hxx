#pragma once
#include <exception>
#include <string>

namespace FeedHistoryDownloader
{
    /// FHD base exception type
    class ExceptionBase : public std::exception
    {
    public:
        /// Ctor.
        /// @param message An error description
        /// @param filename Location of
        ExceptionBase(const std::string & message);

        /// Dtor.
        virtual ~ExceptionBase() throw();

        /// @see std::exception
        const char * what() const throw();
    protected:
        std::string m_message;
    };
}

