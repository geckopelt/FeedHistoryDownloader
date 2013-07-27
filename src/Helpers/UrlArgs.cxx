#include <algorithm>
#include "Helpers/UrlArgs.hxx"

namespace FeedHistoryDownloader
{
	//----------------------------------------------------------------
	void UrlArgs::addArg(const std::string & name, const std::string & value)
	{
		push_back(std::pair<std::string, std::string>(name, value));
	}

	//----------------------------------------------------------------
	const std::string UrlArgs::getArgs() const
	{
		std::string res;
		for (const_iterator it = begin(); it != end(); it++)
		{
			res += makeArg(*it, it == begin() ? '?' : '&');
		}
		return res;
	}

	//----------------------------------------------------------------
	const std::string UrlArgs::makeArg(const std::pair<std::string, std::string> & arg, const char separator) const
	{
		return separator + arg.first + "=" + arg.second;
	}
}
