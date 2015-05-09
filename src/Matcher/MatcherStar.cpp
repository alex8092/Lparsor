#include "Matcher/MatcherStar.h"

using lparsor::matcher::MatcherRepeat;
using lparsor::matcher::MatcherParam;
using lparsor::matcher::MatcherStar;

MatcherStar::MatcherStar(std::vector<MatcherParam>& params) noexcept :
	MatcherRepeat()
{
	std::vector<MatcherParam> to_repeat { 
		MatcherParam(L"0"),
		MatcherParam(L"-1"),
		params[0]
	};
	this->setParams(to_repeat);
}

MatcherStar::~MatcherStar() noexcept
{}