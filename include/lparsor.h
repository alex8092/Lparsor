#ifndef LPARSOR_H
# define LPARSOR_H

# include "Matcher/Exception.h"
# include "Matcher/Mapper.h"
# include "Matcher/MatcherAny.h"
# include "Matcher/MatcherResult.h"
# include "Matcher/MatcherSet.h"
# include "Matcher/MatcherSetReverse.h"
# include "Matcher/MatcherString.h"
# include "Matcher/MatcherParam.h"
# include "Matcher/MatcherList.h"
# include "Matcher/MatcherBegin.h"
# include "Matcher/MatcherEnd.h"
# include "Matcher/MatcherPipe.h"
# include "Matcher/MatcherRepeat.h"
# include "Matcher/MatcherStar.h"
# include "Matcher/MatcherPlus.h"
# include "Matcher/MatcherFactory.h"
# include "Lexer/MatcherLexer.h"
# include "Lexer/LexerFactory.h"
# include "Lexer/Exception.h"
# include "Lexer/Lexem.h"

namespace lparsor
{
	typedef matcher::Exception MatcherException;
	using matcher::Mapper;
	using matcher::MatcherParam;
	using matcher::MatcherResult;
	using matcher::Matcher;
	using matcher::MatcherFactory;

	void init() throw (MatcherException&);
}

#endif