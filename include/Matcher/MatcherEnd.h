#ifndef LPARSOR_MATCHER_END_H
# define LPARSOR_MATCHER_END_H

# include "Matcher/Matcher.h"
# include "Matcher/MatcherResult.h"
# include "Common/string.h"
# include "Matcher/MatcherParam.h"
# include <vector>

namespace lparsor
{
	namespace matcher
	{
		class MatcherEnd : public Matcher
		{
		public:
			explicit 				MatcherEnd(std::vector<MatcherParam>& params) noexcept;
			virtual					~MatcherEnd() noexcept;

			virtual MatcherResult	*match(const lparsor::string& str, size_t index, size_t length);
		};
	}
}

#endif