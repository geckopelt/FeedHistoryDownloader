#pragma once

#include <string>
#include <list>
#include <utility>

namespace FeedHistoryDownloader
{
    /// URL args helper.
    class UrlArgs : public std::list<std::pair<std::string, std::string>>
	{
	public:
		/// Add URL argument.
		/// @param name Argument name.
		/// @param value Argument value.
		void addArg(const std::string & name, const std::string & value);

		/// Get all url args as string.
		/// @return Arguments string.
		const std::string getArgs() const;
	private:
		const std::string makeArg(const std::pair<std::string, std::string> & arg, const char separator) const;
	};
}
