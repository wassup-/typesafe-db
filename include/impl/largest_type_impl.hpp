/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _LARGEST_TYPE_IMPL_HPP
#define _LARGEST_TYPE_IMPL_HPP

#include <type_traits>

namespace fp { namespace impl {
    
    template<typename...>
    struct largest_type_impl;

    namespace {

        template<std::size_t L, std::size_t R>
        struct _max : std::integral_constant<std::size_t, (L < R) ? R : L> { };

        template<std::size_t L, std::size_t R>
        struct _min : std::integral_constant<std::size_t, (L < R) ? L : R> { };
    }

    template<typename H, typename... T>
    struct largest_type_impl<H, T...> : _max<sizeof(H), largest_type_impl<T...>::size> { };

    template<typename T>
    struct largest_type_impl<T> : std::integral_constant<std::size_t, sizeof(T)> { };
} }

#endif