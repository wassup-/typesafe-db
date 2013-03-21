#ifndef _SKIP_VALUES_IMPL_HPP
#define _SKIP_VALUES_IMPL_HPP

namespace fp {
	template<int...> struct int_seq;
	
	namespace impl {
		template<int, bool, int...> struct skip_values_helper;
		template<int, int...> struct skip_values_impl;

		template<int C, int H, int... T> struct skip_values_impl<C, H, T...> {
			typedef typename skip_values_impl<C - 1, T...>::type type;
		};
		template<int H, int... T> struct skip_values_impl<0, H, T...> {
			typedef int_seq<H, T...> type;
		};
		template<> struct skip_values_impl<0> {
			typedef int_seq<> type;
		};

		template<int C, bool S, int... I> struct skip_values_helper {
			typedef typename skip_values_impl<C, I...>::type type;
		};
		template<int C, int... I> struct skip_values_helper<C, true, I...> {
			typedef int_seq<> type;
		};
	}
}

#endif