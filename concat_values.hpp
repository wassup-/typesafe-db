#ifndef _CONCAT_VALUES_HPP
#define _CONCAT_VALUES_HPP


namespace fp {
	template<int...> struct int_seq;
	template<typename, typename> struct concat_values;

	template<int... L, int... R> struct concat_values<int_seq<L...>, int_seq<R...> > {
		typedef int_seq<L..., R...> type;
	};
}

#endif