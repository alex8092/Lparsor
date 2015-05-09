#include "Matcher/MatcherPlus.h"

using lparsor::matcher::MatcherRepeat;
using lparsor::matcher::MatcherParam;
using lparsor::matcher::MatcherPlus;

MatcherPlus::MatcherPlus(std::vector<MatcherParam>& params) noexcept :
	MatcherRepeat()
{
	std::wcout << params[0].getString() << std::endl;
	std::vector<MatcherParam> to_repeat { 
		MatcherParam(L"1"),
		MatcherParam(L"-1"),
		params[0]
	};
	this->setParams(to_repeat);
}

MatcherPlus::~MatcherPlus() noexcept
{}