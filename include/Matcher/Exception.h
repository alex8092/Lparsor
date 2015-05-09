#ifndef LPARSOR_MATCHER_EXCEPTION_H
# define LPARSOR_MATCHER_EXCEPTION_H

# include <exception>

namespace lparsor
{
	namespace matcher
	{
		class Exception : public std::exception
		{
		private:
			const char	*_str;

		public:
			Exception (const char *str) throw() :
				std::exception(),
				_str(str) {}
			Exception (const Exception& e) throw() :
				std::exception(),
				_str(e._str) {}
			Exception& operator= (const Exception& e) throw() {
				std::exception::operator=(e);
				this->_str = e._str;
				return *this;
			}
			virtual ~Exception() throw() {

			}
			virtual const char* what() const throw() {
				return this->_str;
			}
		};
	}
}

#endif