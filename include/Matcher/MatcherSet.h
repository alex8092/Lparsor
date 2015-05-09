#ifndef LPARSOR_MATCHER_SET_H
# define LPARSOR_MATCHER_SET_H

# include "Matcher/Matcher.h"
# include "Matcher/MatcherResult.h"
# include "Matcher/MatcherParam.h"
# include "Common/string.h"
# include <vector>

namespace lparsor
{
	namespace matcher
	{
		class MatcherSet : public Matcher
		{
		private:
			struct Set {
				char32_t 		first;
				char32_t 		end;
				explicit inline Set(char32_t _first, char32_t _end) :
					first(_first), end(_end) {}
			};

			lparsor::string					_content;
			lparsor::string					_match_is_in;
			std::vector<MatcherSet::Set>	_matchs_set;

			void					init() noexcept;

		public:
			explicit 				MatcherSet(std::vector<MatcherParam>& params) noexcept;
			virtual					~MatcherSet() noexcept;

			virtual MatcherResult	*match(const lparsor::string& str, size_t index, size_t length);
		};
	}
}

#endif