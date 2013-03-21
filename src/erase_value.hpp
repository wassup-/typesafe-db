/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _ERASE_VALUE_HPP
#define _ERASE_VALUE_HPP

namespace fp {
	template<int...> struct int_seq;
	template<int, int...> struct erase_value;

	namespace impl {
		template<int, typename, typename> struct erase_value_impl;
		template<int I, int... L, int H, int... T> struct erase_value_impl<I, int_seq<L...>, int_seq<H, T...> > {
			typedef typename erase_value_impl<I - 1, int_seq<L..., H>, int_seq<T...> >::type type;
		};
		template<int... L, int H, int... T> struct erase_value_impl<0, int_seq<L...>, int_seq<H, T...> > {
			typedef int_seq<L..., T...> type;
		};
	}

	template<int I, int... T> struct erase_value {
		typedef typename impl::erase_value_impl<I, int_seq<>, int_seq<T...> >::type type;
	};
}

#endif