#ifndef _LARGEST_TYPE_H
#define _LARGEST_TYPE_H

#include "type_sequence.hpp"

namespace fp {
	template<typename...> struct largest_type;

	namespace impl {
		template<typename...> struct largest_type_impl;

		template<int L, int R> struct _max {
			enum { value = (L < R) ? R : L };
		};
		template<int L, int R> struct _min {
			enum { value = (L < R) ? L : R };
		};

		template<typename H, typename... T> struct largest_type_impl<H, T...> {
			enum { size = _max<sizeof(H), largest_type_impl<T...>::size>::value };
		};
		template<typename T> struct largest_type_impl<T> {
			enum { size = sizeof(T) };
		};
	}

	template<typename... Ts> struct largest_type {
		enum { size = impl::largest_type_impl<Ts...>::size };
	};
	template<typename... Ts> struct largest_type<fp::type_seq<Ts...> > {
		enum { size = impl::largest_type_impl<Ts...>::size };
	};
}

#endif