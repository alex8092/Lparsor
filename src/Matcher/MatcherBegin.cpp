#include "Matcher/MatcherBegin.h"

using lparsor::matcher::Matcher;
using lparsor::matcher::MatcherResult;
using lparsor::matcher::MatcherBegin;
using lparsor::matcher::MatcherParam;

MatcherBegin::MatcherBegin(std::vector<MatcherParam>& params) noexcept :
	Matcher()
{}

MatcherBegin::~MatcherBegin() noexcept {

}

MatcherResult	*MatcherBegin::match(const lparsor::string& str, size_t index, size_t length)
{
	if (index == 0)
		return new MatcherResult(index, 0);
	return nullptr;
}