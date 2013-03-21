#ifndef _LARGEST_VALUE_HPP
#define _LARGEST_VALUE_HPP

namespace fp {
	template<int...> struct largest_value;

	namespace impl {
		template<int, int...> struct largest_value_impl;
		template<int S, int H, int... T> struct largest_value_impl<S, H, T...> {
			enum { value = largest_value_impl<(S >= H)? S : H, T...>::value };
		};
		template<int S> struct largest_value_impl<S> {
			enum { value = S };
		};
	}
	
	template<int H, int... T> struct largest_value<H, T...> {
		enum { value = impl::largest_value_impl<H, T...>::value };
	};
}

#endif