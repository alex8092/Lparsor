#include "Matcher/MatcherFactory.h"
#include <iostream>

using lparsor::matcher::MatcherFactory;
using lparsor::matcher::Matcher;
using lparsor::matcher::MatcherList;
using lparsor::matcher::MatcherParam;
using lparsor::matcher::Mapper;

MatcherFactory	MatcherFactory::_singleton;

Matcher 	*MatcherFactory::createMatcher(const lparsor::string& name, std::vector<MatcherParam>& params)
	throw(lparsor::matcher::Exception&)
{
	auto it = this->_factory_builders.find(name);
	if (it != this->_factory_builders.end()) {
		return it->second(params);
	} else
		throw lparsor::matcher::Exception("Matcher are not registered");
}

lparsor::string		MatcherFactory::_ltrim(const lparsor::string& s, const lparsor::string& space)
{
	size_t i = 0;
	while (space.find_first_of(s[i]) != lparsor::string::npos)
		++i;
	return s.substr(i, s.length() - i);
}

lparsor::string		MatcherFactory::_rtrim(const lparsor::string& s, const lparsor::string& space)
{
	if (s.empty())
		return s;
	size_t i = s.length() - 1;
	while (space.find_first_of(s[i]) != lparsor::string::npos)
		--i;
	return s.substr(0, i + 1);
}

lparsor::string		MatcherFactory::trim(const lparsor::string& s, const lparsor::string& space)
{
	if (s.empty())
		return s;
	return MatcherFactory::_ltrim(MatcherFactory::_rtrim(s, space), space);
}

size_t		MatcherFactory::_find_end(const lparsor::string& regex, size_t index) throw(matcher::Exception&)
{
	const size_t	len = regex.length();
	size_t 			i = index;
	size_t 			count = 0;
	bool			instr = false;
	lparsor::char_t	instr_char;

	for (; i < len; ++i) {
		if (regex[i] == L'(')
			++count;
		else if (regex[i] == L')')
			--count;
		else if (regex[i] == '\\')
			++i;
		else if (regex[i] == L'\'' || regex[i] == L'"') {
			i = MatcherFactory::_find_end_string(regex, i + 1, regex[i]);
			if (i == lparsor::string::npos)
				throw matcher::Exception("Wrong string");
		}
		if (count == 0)
			break ;
	}
	if (i == len)
		return lparsor::string::npos;
	return i;
}

size_t		MatcherFactory::_find_end_string(const lparsor::string& regex, size_t index, lparsor::char_t strdelim)
{
	const size_t 	len = regex.length();
	size_t 			i = index;

	for (; i < len; ++i) {
		if (regex[i] == strdelim)
			return i;
		else if (regex[i] == '\\')
			++i;
	}
	return lparsor::string::npos;
}

std::vector<MatcherParam>	MatcherFactory::_get_params(const lparsor::string& regex, size_t start, Mapper *m)
{
	std::vector<MatcherParam>	params;
	lparsor::string				trimregex = MatcherFactory::trim(regex);
	size_t						len = trimregex.length();
	size_t						i = start;

	for (; i < len; ++i) {
		if (trimregex[i] == L'"' || trimregex[i] == L'\'')
			i = MatcherFactory::instance()->_find_end_string(trimregex, i + 1, trimregex[i]);
		else if (trimregex[i] == L'(')
			i = MatcherFactory::instance()->_find_end(trimregex, i);
		else if (trimregex[i] == L',') {
			lparsor::string		param = MatcherFactory::trim(trimregex.substr(start, i - start));
			if (param[0] == L'"' || param[1] == L'\'')
				params.push_back(MatcherParam(param.substr(1, param.length() - 2)));
			else if (param.find_first_of('(') == lparsor::string::npos)
				params.push_back(MatcherParam(param));
			else
				params.push_back(MatcherParam(MatcherFactory::instance()->get(param, m)));
			start = i + 1;
		}
	}
	if (start < i) {
		lparsor::string 	param = MatcherFactory::trim(trimregex.substr(start, i - start));
		if (param[0] == L'"' || param[0] == L'\'') {
			params.push_back(MatcherParam(param.substr(1, param.length() - 2)));
		}
		else if (param.find_first_of(L'(') == lparsor::string::npos)
			params.push_back(MatcherParam(param));
		else
			params.push_back(MatcherParam(MatcherFactory::instance()->get(param, m)));
	}
	return params;
}

Matcher		*MatcherFactory::get(const lparsor::string& regex, Mapper *m) throw(lparsor::matcher::Exception&)
{
	lparsor::string		trimregex = MatcherFactory::trim(regex);
	Matcher				*last = nullptr;
	MatcherList			*list = nullptr;
	bool				_create = false;

	if (m == nullptr) {
		m = new Mapper();
		_create = true;
	}
	size_t	index = trimregex.find_first_of('(');
	while (index != lparsor::string::npos) {
		size_t end = MatcherFactory::_find_end(trimregex, index);
		if (end == -1)
			throw lparsor::matcher::Exception("Syntax error - missing ')'");
		lparsor::string	name_matcher = MatcherFactory::trim(trimregex.substr(0, index));
		size_t index_key = name_matcher.find_first_of(':');
		lparsor::string key = L"_subs";
		if (index_key != lparsor::string::npos) {
			key = name_matcher.substr(index_key + 1);
			name_matcher = name_matcher.substr(0, index_key);
		}
		auto matcher = MatcherFactory::instance()->_factory_builders.find(name_matcher);
		if (matcher == MatcherFactory::instance()->_factory_builders.end()) {
			std::wcout << L"name matcher: \"" << name_matcher << "\"" << std::endl;
			throw lparsor::matcher::Exception("Unable to find matcher");
		}
		lparsor::string datas = trimregex.substr(index + 1, end - index - 1);
		auto params = MatcherFactory::instance()->_get_params(datas, 0, &m->operator[](key));
		if (params.size() != MatcherFactory::instance()->_number_params[name_matcher]) {
			std::wcout << "name matcher: " << name_matcher << std::endl;
			throw lparsor::matcher::Exception("Wrong number of arguments");
		}
		trimregex = MatcherFactory::trim(trimregex.substr(end + 1));
		index = trimregex.find_first_of('(');
		last = matcher->second(params);
		if (key.compare(L"_subs"))
			m->operator[](key) = last;
		if (index != lparsor::string::npos) {
			if (list == nullptr)
				list = new MatcherList();
			list->add(last);
		}
	}
	if (list != nullptr) {
		list->add(last);
		if (_create)
			delete m;
		return list;
	}
	if (_create)
		delete m;
	return last;
}