#ifndef LPARSOR_MATCHER_PARAM_H
# define LPARSOR_MATCHER_PARAM_H

# include "Matcher/Matcher.h"
# include "Common/string.h"

namespace lparsor
{
	namespace matcher
	{
		class MatcherParam {

		private:
			lparsor::string 				_data;
			Matcher							*_data_matcher = nullptr;

		public:
			explicit inline 				MatcherParam(const lparsor::string& data) :
				_data(data)
			{}
			explicit inline 				MatcherParam(lparsor::string&& data) :
				_data(std::move(data))
			{}
			explicit inline 				MatcherParam(Matcher *data) :
				_data_matcher(data)
			{}
			inline bool 					isMatcher() const noexcept {
				return (this->_data_matcher != nullptr);
			}
			inline Matcher					*getMatcher() noexcept {
				return (this->_data_matcher);
			}
			inline const lparsor::string&	getString() noexcept {
				return (this->_data);
			}
		};
	}
}

#endif