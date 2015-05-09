#include "Lexer/Lexem.h"

using lparsor::lexer::Lexem;
using lparsor::matcher::MatcherResult;

Lexem::Lexem() noexcept
{

}

Lexem::~Lexem() noexcept
{

}

MatcherResult	*Lexem::match(const lparsor::string& str)
{
	if (this->_matcher) {
		MatcherResult	*res = this->_matcher->match(str, 0, str.length());
		if (!res || (res && res->length == 0)) {
			if (res)
				delete res;
			return nullptr;
		}
		return res;
	}
	return nullptr;
}
