#include "Matcher/MatcherSetReverse.h"

using lparsor::matcher::MatcherSet;
using lparsor::matcher::MatcherSetReverse;
using lparsor::matcher::MatcherParam;
using lparsor::matcher::MatcherResult;

MatcherSetReverse::MatcherSetReverse(std::vector<MatcherParam>& params) noexcept :
	MatcherSet(params)
{}

MatcherSetReverse::~MatcherSetReverse() noexcept
{}

MatcherResult	*MatcherSetReverse::match(const lparsor::string& str, size_t index, size_t length)
{
	MatcherResult *res = MatcherSet::match(str, index, length);
	if (res) {
		delete res;
		return nullptr;
	}
	return new MatcherResult(index, 1);
}