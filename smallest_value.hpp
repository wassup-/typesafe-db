/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

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