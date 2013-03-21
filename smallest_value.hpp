#ifndef _SMALLEST_VALUE_HPP
#define _SMALLEST_VALUE_HPP

namespace fp {
	template<int...> struct smallest_value;

	namespace impl {
		template<int, int...> struct smallest_value_impl;
		template<int S, int H, int... T> struct smallest_value_impl<S, H, T...> {
			enum { value = smallest_value_impl<(S <= H)? S : H, T...>::value };
		};
		template<int S> struct smallest_value_impl<S> {
			enum { value = S };
		};
	}
	
	template<int H, int... T> struct smallest_value<H, T...> {
		enum { value = impl::smallest_value_impl<H, T...>::value };
	};
}

#endif