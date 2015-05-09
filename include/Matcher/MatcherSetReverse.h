#ifndef LPARSOR_MATCHER_SETREVERSE_H
# define LPARSOR_MATCHER_SETREVERSE_H

# include "Matcher/MatcherSet.h"
# include "Matcher/MatcherParam.h"
# include "Matcher/MatcherResult.h"
# include "Common/string.h"
# include <vector>

namespace lparsor
{
	namespace matcher
	{
		class MatcherSetReverse : public MatcherSet
		{
		public:
			explicit 				MatcherSetReverse(std::vector<MatcherParam>& params) noexcept;
			virtual					~MatcherSetReverse() noexcept;

			virtual MatcherResult	*match(const lparsor::string& str, size_t index, size_t length);
		};
	}
}

#endif