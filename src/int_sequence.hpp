/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _INT_SEQ_H
#define _INT_SEQ_H

 #include "impl/int_sequence_impl.hpp"

namespace fp {
	template<int...> struct int_seq;
	template<int, int> struct range_builder;

	template<int... Is> struct int_seq {
		enum { size = sizeof...(Is) };

		template<template<int...> class C> struct as {
			typedef C<Is...> type;
		};
	};

	template<int V, int... Vs> struct occurences_of {
		enum { value = impl::occurences_of_impl<0, V, Vs...>::value };
	};

	template<int V, int... Vs> struct index_of {
		enum { value = impl::index_of_impl<0, V, Vs...>::value };
	};

	template<int Min, int Max> struct range_builder {
		typedef typename impl::range_builder_impl<Min <= Max, Min, Max>::type type;	
	};

	template<int Min, int Max> typename range_builder<Min, Max>::type make_range() {
		return typename range_builder<Min, Max>::type();
	}

	template<int V, int... Vs> struct is_contained_int {
		enum { value = impl::is_contained_int_impl<V, Vs...>::value };
	};
};

#endif