#include "Matcher/MatcherPipe.h"
#include <sstream>

using lparsor::matcher::Matcher;
using lparsor::matcher::MatcherParam;
using lparsor::matcher::MatcherResult;
using lparsor::matcher::MatcherPipe;

MatcherPipe::MatcherPipe(std::vector<MatcherParam>& params) noexcept :
	Matcher()
{
	if (params[0].isMatcher() && params[1].isMatcher()) {
		this->_first = params[0].getMatcher();
		this->_second = params[1].getMatcher();
	}
}

MatcherPipe::~MatcherPipe() noexcept
{}

bool			MatcherPipe::hasAlternative() const noexcept
{
	if (this->_do_second)
		return true;
	else if (this->_first != nullptr && this->_second != nullptr)
		return this->_first->hasAlternative() || this->_second->hasAlternative();
	return false;
}

MatcherResult 	*MatcherPipe::alternative()
{
	if (this->_first != nullptr && this->_first->hasAlternative())
		return this->_first->alternative();
	else if (this->_second != nullptr && this->_str != nullptr && this->_do_second)
		return this->_second->match(*this->_str, this->_index, this->_length);
	else if (this->_second != nullptr)
		return this->_second->alternative();
	return nullptr;
}

MatcherResult	*MatcherPipe::match(const lparsor::string& str, size_t index, size_t length)
{
	this->_do_second = true;
	this->_str = &str;
	this->_index = index;
	this->_length = length;
	
	MatcherResult *res = nullptr;

	if (this->_first != nullptr) {
		res = this->_first->match(str, index, length);
	}
	if (res)
		return res;
	else if (this->_second != nullptr) {
		this->_do_second = false;
		return this->_second->match(str, index, length);
	}
	return nullptr;
}