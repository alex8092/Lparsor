#include "Matcher/MatcherSet.h"
#include "Common/string.h"
#include <iostream>

using lparsor::matcher::Matcher;
using lparsor::matcher::MatcherResult;
using lparsor::matcher::MatcherParam;
using lparsor::matcher::MatcherSet;

MatcherSet::MatcherSet(std::vector<MatcherParam>&	params) noexcept : Matcher()
{
	if (!params[0].isMatcher())
		this->_content = params[0].getString();
	this->init();
}

MatcherSet::~MatcherSet() noexcept
{

}

void			MatcherSet::init() noexcept
{
	const lparsor::string&	str = this->_content;	
	lparsor::string&		match_is_in = this->_match_is_in;
	auto&					matchs_set = this->_matchs_set;
	size_t 					len = this->_content.length();

	for (size_t i = 0; i < len; ++i) {
		if (i < len - 2 && str[i + 1] == '-') {
			matchs_set.push_back(std::move(MatcherSet::Set(str[i], str[i + 2])));
		} else if (str[i] == '\\') {
			match_is_in += str[i + 1];
			++i;
		} else {
			match_is_in += str[i];
		}
	}
}

MatcherResult	*MatcherSet::match(const lparsor::string& str, size_t index, size_t length) {
	auto&	matchs_set = this->_matchs_set;
	size_t 	size = matchs_set.size();

	auto test = str[index];
	for (size_t i = 0; i < size; ++i) {
		if (test >= matchs_set[i].first && test <= matchs_set[i].end)
			return (new MatcherResult(index, 1));
	}
	if (this->_match_is_in.find_first_of(test) != lparsor::string::npos)
		return (new MatcherResult(index, 1));
	return nullptr;
}

