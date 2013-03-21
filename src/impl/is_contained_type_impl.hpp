#ifndef _IS_CONTAINED_TYPE_IMPL_HPP
#define _IS_CONTAINED_TYPE_IMPL_HPP

namespace fp {
	namespace impl {
		template<typename, typename...> struct is_contained_type_impl;

		template<typename T, typename H, typename...Ts> struct is_contained_type_impl<T, H, Ts...> {
			enum { value = is_contained_type_impl<T, Ts...>::value };
		};
		template<typename T, typename... Ts> struct is_contained_type_impl<T, T, Ts...> {
			enum { value = true };
		};
		template<typename T, typename H> struct is_contained_type_impl<T, H> {
			enum { value = false };
		};
		template<typename T> struct is_contained_type_impl<T, T> {
			enum { value = true };
		};
	}
}

#endif