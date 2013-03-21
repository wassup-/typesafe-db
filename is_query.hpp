#ifndef _IS_QUERY_HPP
#define _IS_QUERY_HPP

namespace fp {
	template<typename> struct is_query {
		enum { value = false };
	};
}

#endif