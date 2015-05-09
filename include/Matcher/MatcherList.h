#ifndef LPARSOR_MATCHER_LIST_H
# define LPARSOR_MATCHER_LIST_H

# include "Matcher/Matcher.h"
# include "Matcher/MatcherResult.h"
# include "Common/string.h"
# include <vector>

namespace lparsor
{
	namespace matcher
	{
		class MatcherList : public Matcher
		{
		private:
			struct Alternate {
				size_t current_index;
				size_t current_length;
				size_t match;
				explicit inline Alternate(size_t _current_index, size_t _current_length, size_t _match) noexcept :
					current_index(_current_index),
					current_length(_current_length),
					match(_match)
				{}
			};

			std::vector<Alternate>	_alternates;
			std::vector<Matcher*>	_matchers;
			const lparsor::string*	_str;
			size_t					_index;
			size_t					_length;

		public:
			explicit		 		MatcherList() noexcept;
			virtual					~MatcherList() noexcept;

			MatcherList				*add(Matcher *m);
			virtual bool			hasAlternative() const noexcept;
			virtual MatcherResult	*alternative();
			virtual	MatcherResult	*match(const lparsor::string& str, size_t index, size_t length);
		};
	}
}

#endif