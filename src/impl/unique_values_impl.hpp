#ifndef _UNIQUE_VALUES_IMPL_HPP
#define _UNIQUE_VALUES_IMPL_HPP

namespace fp {
	template<int...> struct int_seq;
	
	namespace impl {
		template<bool, typename, typename> struct unique_values_helper;
		template<int... S, int H, int... T> struct unique_values_helper<true, int_seq<S...>, int_seq<H, T...> > {
			typedef typename unique_values_impl<int_seq<S...>, int_seq<T...> >::type type;
		};
		template<int... S, int H, int... T> struct unique_values_helper<false, int_seq<S...>, int_seq<H, T...> > {
			typedef typename unique_values_impl<int_seq<S..., H>, int_seq<T...> >::type type;
		};
	}
}

#endif