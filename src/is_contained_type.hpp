/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _IS_CONTAINED_TYPE_H
#define _IS_CONTAINED_TYPE_H

#include "impl/is_contained_type_impl.hpp"

namespace fp {
	template<typename...> struct type_seq;
	template<typename, typename...> struct is_contained_type;

	template<typename T, typename... Ts> struct is_contained_type {
		enum { value = impl::is_contained_type_impl<T, Ts...>::value };
	};

	template<typename T, typename... Ts> struct is_contained_type<T, type_seq<Ts...> > {
		enum { value = impl::is_contained_type_impl<T, Ts...>::value };
	};
}

#endif