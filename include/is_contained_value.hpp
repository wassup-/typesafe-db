/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _IS_CONTAINED_VALUE_H
#define _IS_CONTAINED_VALUE_H

#include "impl/is_contained_value_impl.hpp"

namespace fp {
    template<int, int...>
    struct is_contained_value;

    template<int T, int... Ts>
    struct is_contained_value : impl::is_contained_value_impl<T, Ts...> {
    };
}

#endif