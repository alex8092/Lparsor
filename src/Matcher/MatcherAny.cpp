#include "Matcher/MatcherAny.h"

using lparsor::matcher::MatcherAny;
using lparsor::matcher::Matcher;
using lparsor::matcher::MatcherResult;
using lparsor::matcher::MatcherParam;

MatcherAny::MatcherAny(std::vector<MatcherParam>& params) noexcept : Matcher() {

}

MatcherAny::~MatcherAny() noexcept {

}

MatcherResult	*MatcherAny::match(const lparsor::string& str, size_t index, size_t length) {
	if (index < length)
		return new MatcherResult(index, 1);
	return nullptr;
}