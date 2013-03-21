#ifndef _TUPLE_CAT_HPP
#define _TUPLE_CAT_HPP

#include <tuple>

namespace fp {
	template<typename...> struct tuple_cat;
	template<typename H, typename... T> struct tuple_cat<H, T...> {
	        static auto cat(H h, T... t) -> decltype(std::tuple_cat(h, tuple_cat<T...>::cat(t...)))
	        { return std::tuple_cat(h, tuple_cat<T...>::cat(t...)); }
	};
	template<typename T> struct tuple_cat<T> {
	        static T cat(T t) { return t; }
	};
}

#endif