#include "Lexer/MatcherLexer.h"
#include "Matcher/MatcherFactory.h"
#include "Lexer/LexerFactory.h"

using lparsor::matcher::MatcherRepeat;
using lparsor::matcher::MatcherParam;
using lparsor::matcher::MatcherResult;
using lparsor::lexer::MatcherLexer;

MatcherLexer::MatcherLexer(std::vector<MatcherParam>& params) noexcept {
	if (params[1].isMatcher()) {
		lparsor::string modifier = std::move(params[0].getString());
		if (!modifier.compare(L"+")) {
			std::vector<MatcherParam> to_repeat { 
				MatcherParam(L"1"),
				MatcherParam(L"-1"),
				params[1]
			};
			this->setParams(to_repeat);
		}
		else if (!modifier.compare(L"*")) {
			std::vector<MatcherParam> to_repeat { 
				MatcherParam(L"0"),
				MatcherParam(L"-1"),
				params[1]
			};
			this->setParams(to_repeat);
		}
		else if (!modifier.compare(L"?")) {
			std::vector<MatcherParam> to_repeat { 
				MatcherParam(L"0"),
				MatcherParam(L"1"),
				params[1]
			};
			this->setParams(to_repeat);
		}
		else {
			std::vector<MatcherParam> to_repeat { 
				MatcherParam(L"1"),
				MatcherParam(L"1"),
				params[1]
			};
			this->setParams(to_repeat);
		}
	} else {
		this->_is_ref = true;
		this->_str_ref = params[1].getString();
	}
}

MatcherLexer::~MatcherLexer() {

}

bool			MatcherLexer::hasAlternative() const noexcept
{
	if (this->_lexem_ref != nullptr)
		return this->_lexem_ref->getMatcher()->hasAlternative();
	return MatcherRepeat::hasAlternative();
}

MatcherResult 	*MatcherLexer::alternative()
{
	if (this->_lexem_ref != nullptr)
		return this->_lexem_ref->getMatcher()->alternative();
	return MatcherRepeat::alternative();
}

MatcherResult	*MatcherLexer::match(const lparsor::string& str, size_t index, size_t length)
{
	if (this->_is_ref) {
		if (this->_lexem_ref == nullptr) {
			this->_lexem_ref = lparsor::lexer::LexerFactory::get(this->_str_ref);
		}
		if (this->_lexem_ref != nullptr)
			return this->_lexem_ref->getMatcher()->match(str, index, length);
		return nullptr;
	}
	return MatcherRepeat::match(str, index, length);
}