#include "Matcher/MatcherString.h"
#include "Matcher/MatcherFactory.h"

using lparsor::matcher::Matcher;
using lparsor::matcher::MatcherParam;
using lparsor::matcher::MatcherResult;
using lparsor::matcher::MatcherString;

MatcherString::MatcherString(std::vector<MatcherParam>& params) noexcept :
	Matcher()
{
	if (!params[0].isMatcher()) {
		this->_to_match = params[0].getString();
	}
}

MatcherString::~MatcherString() noexcept
{

}

MatcherResult	*MatcherString::match(const lparsor::string& str, size_t index, size_t length)
{
	auto& 	to_match = this->_to_match;
	size_t 	size = to_match.size();
	size_t	i;

	for (i = 0; i < size && i + index < length; ++i) {
		if (str[index + i] != to_match[i])
			return nullptr;
	}
	if (i == size)
		return new MatcherResult(index, size);
	return nullptr;
}