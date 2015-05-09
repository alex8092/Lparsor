#ifndef LPARSOR_MATCHER_FACTORY_H
# define LPARSOR_MATCHER_FACTORY_H

# include "Matcher/Exception.h"
# include "Matcher/MatcherParam.h"
# include "Matcher/Matcher.h"
# include "Matcher/Mapper.h"
# include "Matcher/MatcherList.h"
# include "Common/string.h"
# include <vector>
# include <functional>
# include <map>

namespace lparsor
{
	namespace matcher
	{
		template <typename T>
		struct BuilderFactory
		{
			static Matcher* create(std::vector<MatcherParam>& params) noexcept {
				return new T(params);
			}
		};

		class MatcherFactory
		{
		private:
			static MatcherFactory	_singleton;

			std::map<lparsor::string, std::function<Matcher*(std::vector<MatcherParam>&)>>	_factory_builders;
			std::map<lparsor::string, size_t>												_number_params;

			MatcherFactory() = default;
			MatcherFactory(const MatcherFactory&) = delete;
			MatcherFactory(MatcherFactory&&) = delete;
			MatcherFactory& operator=(const MatcherFactory&) = delete;
			MatcherFactory& operator=(MatcherFactory&&) = delete;

			static lparsor::string 				_ltrim(const lparsor::string& s, const lparsor::string& space = lparsor::string(L" \t\n\r"));
			static lparsor::string				_rtrim(const lparsor::string& s, const lparsor::string& space = lparsor::string(L" \t\n\r"));

			static size_t						_find_end(const lparsor::string& name, size_t index) throw(matcher::Exception&);
			static size_t						_find_end_string(const lparsor::string& name, size_t index, lparsor::char_t strdelim);

			std::vector<MatcherParam>			_get_params(const lparsor::string& regex, size_t start, Mapper *m);

		public:

			static lparsor::string				trim(const lparsor::string& s, const lparsor::string& space = lparsor::string(L" \t\n\r"));

			Matcher								*createMatcher(const lparsor::string& name, std::vector<MatcherParam>& params) throw(matcher::Exception&);
			static Matcher						*get(const lparsor::string& name, Mapper *m = nullptr) throw(matcher::Exception&);

			static inline MatcherFactory*		instance() noexcept {
				return &MatcherFactory::_singleton;
			}

			template <class T>
			static MatcherFactory				*registerMatcher(const lparsor::string& name, size_t n_params = 1) throw (matcher::Exception&) {
				auto it = MatcherFactory::instance()->_factory_builders.find(name);
				if (it != MatcherFactory::instance()->_factory_builders.end())
					throw matcher::Exception("Matcher already registered");
				MatcherFactory::instance()->_factory_builders[name] = std::bind(BuilderFactory<T>::create, std::placeholders::_1);
				MatcherFactory::instance()->_number_params[name] = n_params;
				return MatcherFactory::instance();
			}

			
		};
	}
}

#endif