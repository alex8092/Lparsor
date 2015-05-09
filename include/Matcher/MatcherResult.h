#ifndef LPARSOR_MATCHER_RESULT_H
# define LPARSOR_MATCHER_RESULT_H

# include <cstring>
# ifdef LPARSOR_DEBUG
#  include <iostream>
# endif

namespace lparsor
{
	namespace matcher
	{
		struct MatcherResult
		{
			size_t	index;
			size_t	length;
			size_t	next_index;
			explicit inline MatcherResult(size_t _index, size_t _length) :
				index(_index), length(_length), next_index(_index + _length) {}
			inline void	print() {
				#ifdef LPARSOR_DEBUG
				std::wcout << L"Result( index: " << this->index << L" - length: " << this->length << L" - next_index: " << this->next_index << L" )" << std::endl;
				#endif
			}
		};
	}
}

#endif