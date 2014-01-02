/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _SKIP_VALUES_IMPL_HPP
#define _SKIP_VALUES_IMPL_HPP

namespace fp {
    template<typename T, T...>
    struct integer_sequence;

    namespace impl {
        template<int, bool, int...>
        struct skip_values_helper;
        
        template<int, int...>
        struct skip_values_impl;

        template<int C, int H, int... T>
        struct skip_values_impl<C, H, T...> : skip_values_impl<(C - 1), T...> { };

        template<int H, int... T>
        struct skip_values_impl<0, H, T...> {
            using type = integer_sequence<int, H, T...>;
        };

        template<> struct skip_values_impl<0> {
            using type = integer_sequence<int>;
        };

        template<int C, bool S, int... I> struct skip_values_helper : skip_values_impl<C, I...> { };

        template<int C, int... I> struct skip_values_helper<C, true, I...> {
            using type = integer_sequence<int>;
        };
    }
}

#endif