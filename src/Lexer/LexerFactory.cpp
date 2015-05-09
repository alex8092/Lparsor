#include "Lexer/LexerFactory.h"
#include "Matcher/Exception.h"
#include "Lexer/Exception.h"
#include <sstream>

using lparsor::lexer::LexerFactory;
using lparsor::matcher::MatcherFactory;
using lparsor::matcher::MatcherResult;
using lparsor::lexer::Lexem;

LexerFactory 	LexerFactory::_singleton;

LexerFactory::LexerFactory()
{

}

LexerFactory::~LexerFactory() noexcept
{
	
}

void			LexerFactory::init() {
	try {
		this->_named_regex = lparsor::matcher::MatcherFactory::get(L"Begin() Set(a-zA-Z) Star( Set('a-zA-Z0-9_/-') ) End()");
	}
	catch (lparsor::matcher::Exception& e) {
		std::wcout << L"[error] -> " << e.what() << std::endl;
		throw e;
	}
}

lparsor::string		LexerFactory::_subcreate_and(const lparsor::string& pattern, std::vector<lparsor::string>& params)
{
	lparsor::string 				workstr	= MatcherFactory::trim(pattern);
	std::vector<lparsor::string>	tab		= std::move(LexerFactory::split(L"&&", workstr));
	lparsor::string					outstr  = L"";

	for (auto& it : tab) {
		if (it[0] != L'$') {
			if (it[0] == '@') {
				outstr += L"Lexem:" + it.substr(1)+L"('','"+it.substr(1)+L"')";
			} else {
				auto lexem = this->_patterns.find(it);
				if (lexem == this->_patterns.end()) {
					std::wcout << L"lexer: " << it << std::endl;
					throw lparsor::lexer::Exception("Unknow lexer");
				}
				outstr += L"Lexem:"+it+L"('',"+(lexem->second)+L")";
			}
		} else {
			size_t i = 1;
			while (it[i] >= L'0' && it[i] <= L'9')
				++i;
			std::wstringstream ss;
			ss << it.substr(1, i - 1);
			size_t n;
			ss >> n;
			lparsor::string add = it.substr(i);
			bool repeat = true;
			if (!add.compare(L"+"))
				outstr += L"Plus(";
			else if (!add.compare(L"*"))
				outstr += L"Star(";
			else if (!add.compare(L"?"))
				outstr += L"Repeat(0,1,";
			else
				repeat = false;
			outstr += params[n];
			if (repeat)
				outstr += L')';
		}
	}

	return outstr;
}

lparsor::string		LexerFactory::_subcreate_or(const lparsor::string& pattern, std::vector<lparsor::string>& params)
{
	lparsor::string 				workstr	= MatcherFactory::trim(pattern);
	std::vector<lparsor::string>	tab		= std::move(LexerFactory::split(L"||", workstr));
	size_t							count	= 0;

	if (tab.size() > 1) {
		count = 1;
		lparsor::string	outstr = L"Pipe(";
		for (auto& it : tab) {
			outstr += this->_subcreate_and(it, params);
			if (count < tab.size())
				outstr += L",";
			if (count - 1 != 0 && count < tab.size())
				outstr += L"Pipe(";
			++count;
		}
		--count;
		for (;count > 1; --count)
			outstr += L')';
		return outstr;
	} else
		return this->_subcreate_and(pattern, params);
}

lparsor::string		LexerFactory::_subcreate(const lparsor::string& pattern, std::vector<lparsor::string>& params)
{
	lparsor::string	workstr = MatcherFactory::trim(pattern);
	size_t	index = workstr.find_last_of(L'(');
	while (index != lparsor::string::npos) {
		size_t end = workstr.find_first_of(L')', index);
		if (end == lparsor::string::npos)
			throw lparsor::lexer::Exception("Invalid syntax - missing ')'");
		lparsor::string sub = this->_subcreate(workstr.substr(index + 1, end - index - 1), params);
		std::wcout << L"sub: " << sub << std::endl;
		std::wstringstream ss;
		ss << params.size();
		workstr = workstr.substr(0, index) + L"$" + ss.str() + workstr.substr(end + 1);
		params.push_back(sub);
		std::wcout << L"str: " << workstr << std::endl;
		index = workstr.find_last_of(L'(');
	}
	workstr = this->_subcreate_or(workstr, params);
	return workstr;
}

LexerFactory*	LexerFactory::add(const lparsor::string& name, const lparsor::string& pattern)
{
	lparsor::matcher::MatcherResult	*res = this->_named_regex->match(name, 0, name.length());
	if (res && res->length > 0) {
		delete res;
		auto it = this->_patterns.find(name);
		if (it != this->_patterns.end()) {
			std::wcout << L"invalid name [" << name << L"]" << std::endl;
			throw lparsor::lexer::Exception("Lexer already registered");
		}
		size_t len = pattern.length();
		if (pattern[0] == L'{' && pattern[1] == L'{' && pattern[len - 2] == L'}' && pattern[len - 1] == L'}') {
			std::vector<lparsor::string>	params;
			this->_patterns[name] = this->_subcreate(pattern.substr(2, len - 4), params);
			std::wcout << L"Evolved pattern: " << this->_patterns[name] << std::endl;
		} else {
			std::wcout << L"default pattern: " << pattern << std::endl;
			this->_patterns[name] = pattern;
		}
		this->_items[name] = L"Lexem:"+name+L"('',"+this->_patterns[name]+L")";
		return this;
	}
	if (res)
		delete res;
	std::wcout << L"invalid name [" << name << L"]" << std::endl;
	throw lparsor::lexer::Exception("Invalid lexer name");
	return this;
}

Lexem			*LexerFactory::get(const lparsor::string& name)
{
	auto it = LexerFactory::instance()->_items.find(name);
	if (it == LexerFactory::instance()->_items.end())
		return nullptr;
	lparsor::matcher::Mapper	*m = new lparsor::matcher::Mapper();
	lparsor::lexer::Lexem 		*l = new lparsor::lexer::Lexem();
	l->setMatcher(MatcherFactory::instance()->get(it->second, m))
		->setMapper(m);
	return l;
}

std::vector<lparsor::string>	LexerFactory::split(const lparsor::string& separator, const lparsor::string& str)
{
	lparsor::string	workstr = str;
	std::vector<lparsor::string>	tab;

	size_t index = workstr.find(separator);
	while (index != lparsor::string::npos)
	{
		tab.push_back(MatcherFactory::trim(workstr.substr(0, index)));
		workstr = workstr.substr(index + separator.length());
		index = workstr.find(separator);
	}
	tab.push_back(MatcherFactory::trim(workstr));
	return (tab);
}