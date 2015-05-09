#include <ostream>
#include <iostream>
#include "lparsor.h"

using std::ostream;

int	main(void)
{
	lparsor::init();
	lparsor::lexer::LexerFactory::instance()->add(L"digit", L"Set(0-9)");
	lparsor::lexer::LexerFactory::instance()->add(L"alpha", L"Set(a-zA-Z)");
	lparsor::lexer::LexerFactory::instance()->add(L"space", L"Set(' \t')");
	lparsor::lexer::LexerFactory::instance()->add(L"alphanum", L"{{ (digit || alpha)+ }}");
	lparsor::lexer::LexerFactory::instance()->add(L"alphanum-list", L"{{ alphanum && (space || @alphanum-list)* }}");

	auto 					*m = lparsor::lexer::LexerFactory::get(L"alphanum-list");
	lparsor::string			str_test = L"4a4f4ghhhh5h iuoiuoiuo23452345 234iuoiu345oi2u345o2i ";
	try
	{
		auto res = m->match(str_test);
		if (res) {
			res->print();
			delete res;
		}
		delete m;
	}
	catch (lparsor::MatcherException& e) {

	}
	return (0);
}