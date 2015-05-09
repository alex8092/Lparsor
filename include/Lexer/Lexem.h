#ifndef LPARSOR_LEXER_LEXEM_H
# define LPARSOR_LEXER_LEXEM_H

# include "Matcher/Matcher.h"
# include "Matcher/MatcherResult.h"
# include "Matcher/Mapper.h"
# include "Common/string.h"

namespace lparsor
{
	namespace lexer
	{
		class Lexem
		{
		private:
			matcher::Matcher		*_matcher = nullptr;
			matcher::Mapper			*_mapper = nullptr;

		public:
			explicit 				Lexem() noexcept;
			virtual					~Lexem() noexcept;

			inline Lexem			*setMatcher(matcher::Matcher *m) noexcept {
				this->_matcher = m;
				return this;
			}
			inline Lexem 			*setMapper(matcher::Mapper *m) noexcept {
				this->_mapper = m;
				return this;
			}

			inline matcher::Matcher *getMatcher() noexcept {
				return this->_matcher;
			}

			inline matcher::Mapper	*getMapper() noexcept {
				return this->_mapper;
			}

			matcher::MatcherResult	*match(const lparsor::string& str);

		};
	}
}

#endif