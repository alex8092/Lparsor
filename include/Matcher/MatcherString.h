#ifndef LPARSOR_MATCHER_STRING_H
# define LPARSOR_MATCHER_STRING_H

# include "Matcher/Matcher.h"
# include "Matcher/MatcherParam.h"
# include "Matcher/MatcherResult.h"
# include "Common/string.h"
# include <vector>

namespace lparsor
{
	namespace matcher
	{
		class MatcherString : public Matcher
		{
		private:
			lparsor::string 	_to_match;
		public:
			explicit 					MatcherString(std::vector<MatcherParam>& params) noexcept;
			virtual						~MatcherString() noexcept;

			virtual MatcherResult		*match(const lparsor::string& str, size_t index, size_t length);
		};
	}
}

#endif