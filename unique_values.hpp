/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _UNIQUE_VALUES_HPP
#define _UNIQUE_VALUES_HPP

#include "int_sequence.hpp"
#include "nth_value_of.hpp"

namespace fp {
	template<int...> struct unique_values;
	template<typename, typename> struct unique_values_impl;

	namespace impl {
		template<bool, typename, typename> struct unique_values_helper;
		template<int... S, int H, int... T> struct unique_values_helper<true, int_seq<S...>, int_seq<H, T...> > {
			typedef typename unique_values_impl<int_seq<S...>, int_seq<T...> >::type type;
		};
		template<int... S, int H, int... T> struct unique_values_helper<false, int_seq<S...>, int_seq<H, T...> > {
			typedef typename unique_values_impl<int_seq<S..., H>, int_seq<T...> >::type type;
		};
	}

	template<int... S, int H, int... T> struct unique_values_impl<int_seq<S...>, int_seq<H, T...> > {
		enum { last = last_value_of<S...>::value };

		typedef typename impl::unique_values_helper<(H == last), int_seq<S...>, int_seq<H, T...> >::type type;
	};

	template<int... S> struct unique_values_impl<int_seq<S...>, int_seq<> > {
		typedef int_seq<S...> type;
	};

	template<int H, int... T> struct unique_values<H, T...> {
		typedef typename unique_values_impl<int_seq<H>, int_seq<T...> >::type type;
	};
}

#endif