#pragma once
#include <exception>
#include "Exceptions/ExceptionBase.hxx"

namespace FeedHistoryDownloader
{
    /// Guard violation exception.
    class GuardException : public ExceptionBase
    {
    public:
        /// Ctor.
        /// @param message An error description
        /// @param filename Location of a guard clause
        GuardException(const std::string & message, const std::string & filename, size_t line);

        /// Get filename.
        const std::string & getFilename() const;

        /// @see std::exception
        const char * what() const throw();

        virtual ~GuardException() throw();

    private:
        std::string m_filename;
        std::string m_what;
        int m_line;
    };
}

