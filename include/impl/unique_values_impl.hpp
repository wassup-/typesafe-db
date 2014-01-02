/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _UNIQUE_VALUES_IMPL_HPP
#define _UNIQUE_VALUES_IMPL_HPP

#include "../is_contained_value.hpp"
#include "../type_traits.hpp"

namespace fp {
    template<typename T, T...>
    struct integer_sequence;

    namespace impl {
        template<typename, typename>
        struct unique_values_impl;
        
        template<bool, typename, typename>
        struct unique_values_helper;

        template<typename T, T... TLeft, T H, T... R>
        struct unique_values_impl<integer_sequence<T, TLeft...>, integer_sequence<T, H, R...> >
        : unique_values_helper<is_contained_value<T, H, TLeft...>::value, integer_sequence<T, TLeft...>, integer_sequence<T, H, R...>> { };

        template<typename T, T... TLeft>
        struct unique_values_impl<integer_sequence<T, TLeft...>, integer_sequence<T>> : identity<integer_sequence<T, TLeft...>> { };

        template<typename T, T... TLeft, T THead, T... TTail>
        struct unique_values_helper<false, integer_sequence<T, TLeft...>, integer_sequence<T, THead, TTail...> >
        : unique_values_impl<integer_sequence<T, TLeft..., THead>, integer_sequence<T, TTail...> > { };

        template<typename T, T... TLeft, T THead, T... TTail>
        struct unique_values_helper<true, integer_sequence<T, TLeft...>, integer_sequence<T, THead, TTail...> >
        : unique_values_impl<integer_sequence<T, TLeft...>, integer_sequence<T, TTail...>> { };
    }
}

#endif