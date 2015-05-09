#ifndef LPARSOR_MATCHER_PLUS_H
# define LPARSOR_MATCHER_PLUS_H

# include "Matcher/MatcherRepeat.h"
# include "Matcher/MatcherParam.h"
# include "Common/string.h"
# include <vector>

namespace lparsor
{
	namespace matcher
	{
		class MatcherPlus : public MatcherRepeat
		{
		public:
			explicit 	MatcherPlus(std::vector<MatcherParam>& params) noexcept;
			virtual		~MatcherPlus() noexcept;
		};
	}
}

#endif