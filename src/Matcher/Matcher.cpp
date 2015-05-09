#include "Matcher/Matcher.h"

using lparsor::matcher::Matcher;
using lparsor::matcher::MatcherResult;

Matcher::Matcher() noexcept {}
Matcher::~Matcher() noexcept {}

bool			Matcher::hasAlternative() const noexcept {
	return false;
}

MatcherResult	*Matcher::alternative() {
	return nullptr;
}

MatcherResult	*Matcher::match(const lparsor::string& str, size_t index, size_t length) {
	return nullptr;
}