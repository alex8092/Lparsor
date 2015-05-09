#ifndef LPARSOR_MATCHER_STAR_H
# define LPARSOR_MATCHER_STAR_H

# include "Matcher/MatcherRepeat.h"
# include "Matcher/MatcherParam.h"
# include "Common/string.h"
# include <vector>

namespace lparsor
{
	namespace matcher
	{
		class MatcherStar : public MatcherRepeat
		{
		public:
			explicit 	MatcherStar(std::vector<MatcherParam>& params) noexcept;
			virtual		~MatcherStar() noexcept;
		};
	}
}

#endif