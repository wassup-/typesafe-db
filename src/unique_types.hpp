/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _UNIQUE_TYPES_HPP
#define _UNIQUE_TYPES_HPP

#include "is_contained_type.hpp"

namespace fp {
	template<typename...> struct type_seq;
	template<typename...> struct unique_types;

	namespace impl {
		template<typename, typename> struct unique_types_impl;
		template<bool, typename, typename> struct unique_types_helper;


		template<typename... TLeft, typename H, typename... T>
		struct unique_types_impl<type_seq<TLeft...>, type_seq<H, T...> > {
			typedef typename unique_types_helper<is_contained_type<H, TLeft...>::value, type_seq<TLeft...>, type_seq<H, T...> >::type type;
		};

		template<typename... TLeft>
		struct unique_types_impl<type_seq<TLeft...>, type_seq<> > {
			typedef type_seq<TLeft...> type;
		};

		template<typename... TLeft, typename TRightHead, typename... TRightTail>
		struct unique_types_helper<false, type_seq<TLeft...>, type_seq<TRightHead, TRightTail...> > {
			typedef typename unique_types_impl<type_seq<TLeft..., TRightHead>, type_seq<TRightTail...> >::type type;
		};

		template<typename... TLeft, typename TRightHead, typename... TRightTail>
		struct unique_types_helper<true, type_seq<TLeft...>, type_seq<TRightHead, TRightTail...> > {
			typedef typename unique_types_impl<type_seq<TLeft...>, type_seq<TRightTail...> >::type type;
		};
	}

	template<typename H, typename... T> struct unique_types<H, T...> {
		typedef typename impl::unique_types_impl<type_seq<H>, type_seq<T...> >::type type;
	};
}

#endif