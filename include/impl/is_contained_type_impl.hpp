/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _IS_CONTAINED_TYPE_IMPL_HPP
#define _IS_CONTAINED_TYPE_IMPL_HPP

#include "../type_traits.hpp"

namespace fp { namespace impl {

    template<typename, typename...>
    struct is_contained_type_impl;

    template<typename T, typename H, typename... Ts>
    struct is_contained_type_impl<T, H, Ts...> : is_contained_type_impl<T, Ts...> { };

    template<typename T, typename... Ts>
    struct is_contained_type_impl<T, T, Ts...> : std::true_type { };

    template<typename T, typename H>
    struct is_contained_type_impl<T, H> : std::false_type { };

    template<typename T>
    struct is_contained_type_impl<T, T> : std::true_type { };
} }

#endif