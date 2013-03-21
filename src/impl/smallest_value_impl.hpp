#ifndef _SMALLEST_VALUE_IMPL_HPP
#define _SMALLEST_VALUE_IMPL_HPP

namespace fp {
	namespace impl {
		template<int, int...> struct smallest_value_impl;
		template<int S, int H, int... T> struct smallest_value_impl<S, H, T...> {
			enum { value = smallest_value_impl<(S <= H)? S : H, T...>::value };
		};
		template<int S> struct smallest_value_impl<S> {
			enum { value = S };
		};
	}
}

#endif