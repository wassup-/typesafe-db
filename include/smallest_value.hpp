/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _SMALLEST_VALUE_HPP
#define _SMALLEST_VALUE_HPP

#include "impl/smallest_value_impl.hpp"

namespace fp {
	
    template<typename T, T... Vs>
    struct smallest_value : impl::smallest_value_impl<T, Vs...> { };
}

#endif