#ifndef LPARSOR_LEXER_LEXERFACTORY_H
# define LPARSOR_LEXER_LEXERFACTORY_H

# include "Common/string.h"
# include "Matcher/Matcher.h"
# include "Matcher/MatcherResult.h"
# include "Matcher/MatcherFactory.h"
# include "Lexer/Lexem.h"
# include <vector>

namespace lparsor
{
	namespace lexer
	{
		class LexerFactory
		{
		private:
			static LexerFactory 	_singleton;

			explicit 	LexerFactory();
			LexerFactory(LexerFactory&) = delete;
			LexerFactory(LexerFactory&&) = delete;
			LexerFactory& operator=(LexerFactory&) = delete;
			LexerFactory& operator=(LexerFactory&&) = delete;
		
			matcher::Matcher 							*_named_regex = nullptr;
			std::map<lparsor::string, lparsor::string>	_patterns;
			std::map<lparsor::string, lparsor::string>	_items;

			lparsor::string						_subcreate_and(const lparsor::string& pattern, std::vector<lparsor::string>& params);
			lparsor::string						_subcreate_or(const lparsor::string& pattern, std::vector<lparsor::string>& params);
			lparsor::string						_subcreate(const lparsor::string& pattern, std::vector<lparsor::string>& params);

		public:
			virtual								~LexerFactory() noexcept;

			static std::vector<lparsor::string>	split(const lparsor::string& separator, const lparsor::string& str);

			void								init();

			LexerFactory*						add(const lparsor::string& name, const lparsor::string& pattern);

			static Lexem						*get(const lparsor::string& name);

			static inline LexerFactory*			instance() noexcept {
				return (&LexerFactory::_singleton);
			}
		};
	}
}

#endif