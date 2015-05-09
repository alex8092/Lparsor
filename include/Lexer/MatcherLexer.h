#ifndef LPARSOR_LEXER_MATCHER_H
# define LPARSOR_LEXER_MATCHER_H

# include "Matcher/MatcherRepeat.h"
# include "Matcher/MatcherParam.h"
# include "Matcher/MatcherResult.h"
# include "Lexer/Lexem.h"
# include "Common/string.h"
# include <vector>

namespace lparsor
{
	namespace lexer
	{
		class MatcherLexer : public matcher::MatcherRepeat
		{
		private:
			Lexem				*_lexem_ref = nullptr;
			bool				_is_ref = false;
			lparsor::string		_str_ref;

		public:
			explicit 						MatcherLexer(std::vector<matcher::MatcherParam>& params) noexcept;
			virtual							~MatcherLexer() noexcept;

			virtual bool					hasAlternative() const noexcept;
			virtual matcher::MatcherResult	*alternative();
			virtual matcher::MatcherResult	*match(const lparsor::string& str, size_t index, size_t length);
		};
	}
}

#endif