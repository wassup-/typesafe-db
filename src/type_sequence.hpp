/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _TYPE_SEQ_H
#define _TYPE_SEQ_H

namespace fp {
	template<typename...> struct type_seq;
	template<typename...> struct pack_types;

	template<typename... Ts> struct type_seq {
		enum { size = sizeof...(Ts) };

		template<typename T> struct extend {
			typedef type_seq<Ts..., T> type;
		};

		template<template<typename...> class C> struct as {
			typedef C<Ts...> type;
		};
	};

	namespace impl {
		template<typename, typename...> struct extend_impl;

		template<typename... S, typename... E> struct extend_impl<type_seq<S...>, E...> {
			typedef type_seq<S..., E...> type;
		};
	}

	template<typename... Ts> struct pack_types {
		typedef type_seq<Ts...> type;
	};
};

#endif