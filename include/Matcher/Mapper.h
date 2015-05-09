#ifndef LPARSOR_MATCHER_MAPPER_H
# define LPARSOR_MATCHER_MAPPER_H

# include "Matcher/Matcher.h"
# include "Common/string.h"
# include "Matcher/Exception.h"
# include <map>

namespace lparsor
{
	namespace matcher
	{
		class Mapper;

		typedef std::map<lparsor::string, Mapper> MapperData;

		class Mapper
		{
		private:
			MapperData								*_subs = nullptr;
			Matcher									*_matcher = nullptr;

		public:
			inline Mapper(Matcher *m) :
				_matcher(m) {}
			inline Mapper() {}

			inline bool isMatcher() const noexcept {
				return (this->_matcher != nullptr);
			}

			inline bool hasMapper() const noexcept {
				return (this->_subs != nullptr);
			}

			inline operator Matcher* () throw(matcher::Exception&) {
				if (this->_matcher == nullptr)
					throw matcher::Exception("Not a matcher");
				return (this->_matcher);
			}

			inline MapperData::iterator begin() {
				if (!this->_subs)
					this->_subs = new MapperData();
				return this->_subs->begin();
			}

			inline MapperData::iterator end() {
				if (!this->_subs)
					this->_subs = new MapperData();
				return this->_subs->end();
			}

			virtual Mapper& operator[](const lparsor::string& key) {
				if (!this->_subs)
					this->_subs = new MapperData();
				return this->_subs->operator[](key);
			}

			inline Mapper&	operator=(Matcher *m) noexcept {
				this->_matcher = m;
				return *this;
			}

			static void	print(Mapper& mapper, int level = 0) {
				#ifdef LPARSOR_DEBUG
				for (auto& it : mapper) {
					for (size_t i = 0; i < level; ++i)
						std::wcout << "\t";
					std::wcout << L"[" << it.first << L"]";
					if (it.second.isMatcher())
						std::wcout << "-> " << static_cast<Matcher*>(it.second) << std::endl;
					else
						std::wcout << std::endl;
					if (it.second.hasMapper())
						print(it.second, level + 1);
				}
				#endif
			}
		};
	}
}

#endif