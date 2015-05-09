#include "Matcher/MatcherList.h"

using lparsor::matcher::Matcher;
using lparsor::matcher::MatcherResult;
using lparsor::matcher::MatcherList;

MatcherList::MatcherList() noexcept :
	Matcher()
{}

MatcherList::~MatcherList() noexcept {
	for (auto it : this->_matchers) {
		delete it;
	}
}

MatcherList		*MatcherList::add(Matcher *m) {
	if (m != nullptr) {
		this->_matchers.push_back(m);
	}
	return (this);
}

bool			MatcherList::hasAlternative() const noexcept
{
	if (this->_alternates.size() > 0)
		return true;
	return false;
}

MatcherResult	*MatcherList::alternative()
{
	if (this->_alternates.size() > 0 && this->_str != nullptr) {
		auto&& 			alternate = std::move(this->_alternates.back());
		this->_alternates.pop_back();
		auto& 			str = *this->_str;
		size_t  		index = this->_index;
		size_t 			length = this->_length;
		size_t			current_index = alternate.current_index;
		size_t			current_length = alternate.current_length;
		auto&			matchers = this->_matchers;
		size_t			len = matchers.size();
		MatcherResult	*res = nullptr;

		res = matchers[alternate.match]->alternative();
		if (res == nullptr)
			return nullptr;
		if (matchers[alternate.match]->hasAlternative())
			this->_alternates.push_back(alternate);
		current_length += res->length;
		current_index = res->next_index;
		delete res;
		for (size_t i = alternate.match + 1; i < len; ++i) {
			res = matchers[i]->match(str, current_index, length);
			if (matchers[i]->hasAlternative())
				this->_alternates.push_back(MatcherList::Alternate(current_index, current_length, i));
			if (res != nullptr) {
				current_length += res->length;
				current_index = res->next_index;
				delete res;
			} else if (this->hasAlternative())
				return this->alternative();
			else
				return nullptr;
		}
		return new MatcherResult(index, current_length);
	}
	return nullptr;
}

MatcherResult	*MatcherList::match(const lparsor::string& str, size_t index, size_t length)
{
	size_t 			current_length = 0;
	auto&			matchers = this->_matchers;
	size_t			len = matchers.size();
	size_t			current_index = index;
	MatcherResult	*res = nullptr;

	this->_str = &str;
	this->_index = index;
	this->_length = length;
	for (size_t i = 0; i < len; ++i) {
		res = matchers[i]->match(str, current_index, length);
		if (matchers[i]->hasAlternative())
			this->_alternates.push_back(MatcherList::Alternate(current_index, current_length, i));
		if (res) {
			current_length += res->length;
			current_index = res->next_index;
			delete res;
		} else if (this->hasAlternative())
			return this->alternative();
		else
			return nullptr;
	}
	return new MatcherResult(index, current_length);
}