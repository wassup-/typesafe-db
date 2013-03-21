/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _DROP_VALUES_HPP
#define _DROP_VALUES_HPP

namespace fp {
	template<int...> struct int_seq;
	template<int, int...> struct drop_values;

	namespace impl {
		namespace {
			template<int...> struct first_value_of;
			template<int H, int... T> struct first_value_of<H, T...> 	{ enum { value = H }; };
			template<int...> struct skip_one;
			template<int H, int... T> struct skip_one<H, T...> 			{ typedef int_seq<T...> type; };
		}
		template<int, bool, typename, typename> struct drop_values_impl;
		template<int C, bool S, int... L, int... R> struct drop_values_impl<C, S, int_seq<L...>, int_seq<R...> > {
			typedef typename drop_values_impl<C, (C == sizeof...(R) - 1), int_seq<L..., first_value_of<R...>::value>, typename skip_one<R...>::type >::type type;
		};
		template<int C, int... L, int... R> struct drop_values_impl<C, true, int_seq<L...>, int_seq<R...> > {
			typedef int_seq<L...> type;
		};
	}

	template<int C, int... I> struct drop_values {
		typedef typename impl::drop_values_impl<C, (C == sizeof...(I)), int_seq<>, int_seq<I...> >::type type;
	};
	template<int C, int... I> struct drop_values_or_empty {
		typedef typename impl::drop_values_impl<C, (C >= sizeof...(I)), int_seq<>, int_seq<I...> >::type type;
	};
}

#endif