#ifndef LPARSOR_MATCHER_BEGIN_H
# define LPARSOR_MATCHER_BEGIN_H

# include "Matcher/Matcher.h"
# include "Matcher/MatcherResult.h"
# include "Common/string.h"
# include "Matcher/MatcherParam.h"
# include <vector>

namespace lparsor
{
	namespace matcher
	{
		class MatcherBegin : public Matcher
		{
		public:
			explicit 				MatcherBegin(std::vector<MatcherParam>& params) noexcept;
			virtual					~MatcherBegin() noexcept;

			virtual MatcherResult	*match(const lparsor::string& str, size_t index, size_t length);
		};
	}
}

#endif