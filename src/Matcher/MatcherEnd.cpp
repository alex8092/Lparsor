#include "Matcher/MatcherEnd.h"

using lparsor::matcher::Matcher;
using lparsor::matcher::MatcherResult;
using lparsor::matcher::MatcherEnd;
using lparsor::matcher::MatcherParam;

MatcherEnd::MatcherEnd(std::vector<MatcherParam>& params) noexcept :
	Matcher()
{}

MatcherEnd::~MatcherEnd() noexcept {

}

MatcherResult	*MatcherEnd::match(const lparsor::string& str, size_t index, size_t length)
{
	if (index == length)
		return new MatcherResult(index, 0);
	return nullptr;
}