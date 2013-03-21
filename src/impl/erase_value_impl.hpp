#ifndef _ERASE_VALUE_IMPL_HPP
#define _ERASE_VALUE_IMPL_HPP

namespace fp {
	template<int...> struct int_seq;
	template<typename...> struct type_seq;
	
	namespace impl {
		template<int, typename, typename> struct erase_value_impl;
		template<int I, int... L, int H, int... T> struct erase_value_impl<I, int_seq<L...>, int_seq<H, T...> > {
			typedef typename erase_value_impl<I - 1, int_seq<L..., H>, int_seq<T...> >::type type;
		};
		template<int... L, int H, int... T> struct erase_value_impl<0, int_seq<L...>, int_seq<H, T...> > {
			typedef int_seq<L..., T...> type;
		};
	}
}

#endif