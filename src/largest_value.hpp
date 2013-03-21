/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _LARGEST_VALUE_HPP
#define _LARGEST_VALUE_HPP

 #include "impl/largest_value_impl.hpp"

namespace fp {
	template<int...> struct largest_value;

	template<int H, int... T> struct largest_value<H, T...> {
		enum { value = impl::largest_value_impl<H, T...>::value };
	};
}

#endif