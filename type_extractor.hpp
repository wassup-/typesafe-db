#ifndef _TYPE_EXTRACTOR_HPP
#define _TYPE_EXTRACTOR_HPP

#include "int_sequence.hpp"
#include "type_sequence.hpp"

namespace fp {
	template<typename, typename> struct extract_types;

	template<int... I, typename... T> struct extract_types<int_seq<I...>, type_seq<T...> > {
		typedef type_seq<typename nth_type_of<I, T...>::type...> type;
	};
}

#endif