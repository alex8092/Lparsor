#ifndef LPARSOR_MATCHER_ANY_H
# define LPARSOR_MATCHER_ANY_H

# include "Matcher/Matcher.h"
# include "Matcher/MatcherResult.h"
# include "Common/string.h"
# include "Matcher/MatcherParam.h"
# include <vector>

namespace lparsor
{
	namespace matcher
	{
		class MatcherAny : public Matcher
		{
		private:

		public:
			explicit 				MatcherAny(std::vector<MatcherParam>& params) noexcept;
			virtual					~MatcherAny() noexcept;

			virtual MatcherResult	*match(const lparsor::string& str, size_t index, size_t length);
		};
	}
}

#endif