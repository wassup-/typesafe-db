/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _SKIP_VALUES_HPP
#define _SKIP_VALUES_HPP

#include "impl/skip_values_impl.hpp"

namespace fp {
	template<int, int...> struct skip_values;

	template<int C, int... I> struct skip_values {
		typedef typename impl::skip_values_helper<C, false, I...>::type type;
	};

	template<int C, int... I> struct skip_values_or_empty {
		typedef typename impl::skip_values_impl<C, (C >= sizeof...(I)), I...>::type type;
	};
}

#endif