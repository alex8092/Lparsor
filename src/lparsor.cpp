#include "lparsor.h"

void	lparsor::init() throw(lparsor::MatcherException&) {
	static bool		isinit = false;

	if (!isinit) {
		lparsor::MatcherFactory::registerMatcher<lparsor::matcher::MatcherAny>(L"Any", 0);
		lparsor::MatcherFactory::registerMatcher<lparsor::matcher::MatcherBegin>(L"Begin", 0);
		lparsor::MatcherFactory::registerMatcher<lparsor::matcher::MatcherEnd>(L"End", 0);
		lparsor::MatcherFactory::registerMatcher<lparsor::matcher::MatcherPipe>(L"Pipe", 2);
		lparsor::MatcherFactory::registerMatcher<lparsor::matcher::MatcherPlus>(L"Plus", 1);
		lparsor::MatcherFactory::registerMatcher<lparsor::matcher::MatcherRepeat>(L"Repeat", 3);
		lparsor::MatcherFactory::registerMatcher<lparsor::matcher::MatcherSet>(L"Set", 1);
		lparsor::MatcherFactory::registerMatcher<lparsor::matcher::MatcherSetReverse>(L"SetReverse", 1);
		lparsor::MatcherFactory::registerMatcher<lparsor::matcher::MatcherStar>(L"Star", 1);
		lparsor::MatcherFactory::registerMatcher<lparsor::matcher::MatcherString>(L"String", 1);
		lparsor::MatcherFactory::registerMatcher<lparsor::lexer::MatcherLexer>(L"Lexem", 2);
		lparsor::lexer::LexerFactory::instance()->init();
		isinit = true;
	}
}