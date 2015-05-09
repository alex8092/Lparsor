#include "Matcher/MatcherRepeat.h"
#include <sstream>

using lparsor::matcher::Matcher;
using lparsor::matcher::MatcherParam;
using lparsor::matcher::MatcherResult;
using lparsor::matcher::MatcherRepeat;

MatcherRepeat::MatcherRepeat() noexcept :
	Matcher()
{

}

void	MatcherRepeat::setParams(std::vector<MatcherParam>& params) noexcept
{
	size_t 	tmp;
	ssize_t	tmp2;

	std::wstringstream	ss(params[0].getString());
	ss >> tmp;
	this->_min = tmp;
	std::wstringstream	ss2(params[1].getString());
	ss2 >> tmp2;
	this->_max = tmp2;
	if (params[2].isMatcher())
		this->_matcher = params[2].getMatcher();
	else
		this->_matcher = new Matcher();
	this->_current_index = 0;
}

MatcherRepeat::MatcherRepeat(std::vector<MatcherParam>& params) noexcept :
	Matcher()
{
	this->setParams(params);
}

MatcherRepeat::~MatcherRepeat() noexcept
{}

bool			MatcherRepeat::hasAlternative() const noexcept
{
	if (this->_results.size() > 0)
		return true;
	return false;
}

MatcherResult 	*MatcherRepeat::alternative()
{
	auto& 			results = this->_results;

	if (results.size() > 0) {
		auto&& res = std::move(results.back());
		results.pop_back();
		return (new MatcherResult(this->_current_index, res.index - this->_current_index + res.length));
	}
	return (nullptr);
}

MatcherResult	*MatcherRepeat::match(const lparsor::string& str, size_t index, size_t length)
{
	if (!this->_matcher)
		return nullptr;
	size_t			current_index = index;
	size_t			current_length = 0;
	size_t			current_nb = 0;
	MatcherResult	*res = nullptr;

	this->_current_index = index;
	this->_results.clear();

	if (this->_min == 0)
		this->_results.push_back(std::move(MatcherResult(index, 0)));
	while ((this->_max == -1 || current_nb < (size_t)this->_max) && current_index < length) {
		res = this->_matcher->match(str, current_index, length);
		if (res != nullptr) {
			this->_results.push_back(std::move(MatcherResult(*res)));
			current_index = res->next_index;
			current_length += res->length;
			++current_nb;
			delete res;
		} else
			break ;
	}
	if ((current_nb >= this->_min && (ssize_t)current_nb <= this->_max)
		|| (current_nb >= this->_min && this->_max == -1))
		return new MatcherResult(index, current_length);
	return nullptr;
}