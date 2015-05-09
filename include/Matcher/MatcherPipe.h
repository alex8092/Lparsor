#ifndef LPARSOR_MATCHER_PIPE_H
# define LPARSOR_MATCHER_PIPE_H

# include "Matcher/Matcher.h"
# include "Matcher/MatcherParam.h"
# include "Matcher/MatcherResult.h"
# include "Common/string.h"
# include <vector>

namespace lparsor
{
	namespace matcher
	{
		class MatcherPipe : public Matcher
		{
		private:
			Matcher 				*_first = nullptr;
			Matcher 				*_second = nullptr;
			bool					_do_second = false;
			const lparsor::string	*_str = nullptr;
			size_t					_index;
			size_t					_length;

		public:
			explicit 				MatcherPipe(std::vector<MatcherParam>& params) noexcept;
			virtual					~MatcherPipe() noexcept;

			virtual bool			hasAlternative() const noexcept;
			virtual MatcherResult	*alternative();
			virtual MatcherResult	*match(const lparsor::string& str, size_t index, size_t length);
		};
	}
}

#endif