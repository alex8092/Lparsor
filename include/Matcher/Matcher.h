#ifndef LPARSOR_MATCHER_H
# define LPARSOR_MATCHER_H

# include "Matcher/MatcherResult.h"
# include "Common/string.h"

namespace lparsor
{
	namespace matcher
	{
		class Matcher
		{
		private:

		public:
			explicit 				Matcher() noexcept;
			virtual					~Matcher() noexcept;

			virtual bool			hasAlternative() const noexcept;
			virtual MatcherResult	*alternative();
			virtual MatcherResult	*match(const lparsor::string& str, size_t index, size_t length);
		};
	}
}

#endif