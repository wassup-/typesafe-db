/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _IS_CONTAINED_TYPE_H
#define _IS_CONTAINED_TYPE_H

#include "type_sequence.hpp"

namespace fp {
	template<typename, typename...> struct is_contained_type;

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

	template<typename T, typename... Ts> struct is_contained_type {
		enum { value = impl::is_contained_type_impl<T, Ts...>::value };
	};

	template<typename T, typename... Ts> struct is_contained_type<T, type_seq<Ts...> > {
		enum { value = impl::is_contained_type_impl<T, Ts...>::value };
	};
}

#endif