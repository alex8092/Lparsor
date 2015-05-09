#ifndef LPARSOR_MATCHER_REPEAT_H
# define LPARSOR_MATCHER_REPEAT_H

# include "Matcher/Matcher.h"
# include "Matcher/MatcherParam.h"
# include "Matcher/MatcherResult.h"
# include "Common/string.h"
# include <vector>

namespace lparsor
{
	namespace matcher
	{
		class MatcherRepeat : public Matcher
		{
		private:
			size_t							_min = 0;
			ssize_t							_max = 0;
			size_t							_current_index;
			std::vector<MatcherResult>		_results;
			Matcher							*_matcher;

		protected:
			explicit				MatcherRepeat() noexcept;
			virtual void			setParams(std::vector<MatcherParam>& params) noexcept;

		public:
			explicit 				MatcherRepeat(std::vector<MatcherParam>& params) noexcept;
			virtual					~MatcherRepeat() noexcept;

			virtual bool			hasAlternative() const noexcept;
			virtual MatcherResult	*alternative();
			virtual MatcherResult	*match(const lparsor::string& str, size_t index, size_t length);
		};
	}
}

#endif