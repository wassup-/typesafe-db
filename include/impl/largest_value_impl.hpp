/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _LARGEST_VALUE_IMPL_HPP
#define _LARGEST_VALUE_IMPL_HPP

#include <type_traits>

namespace fp { namespace impl {

    template<typename T, T, T...>
    struct largest_value_impl;

    template<typename T, T S, T H, T... R>
    struct largest_value_impl<S, H, R...> : largest_value_impl<T, ((S >= H) ? S : H), R...> { };

    template<typename T, T S>
    struct largest_value_impl<S> : mpl::const_<T, S> { };
} }

#endif