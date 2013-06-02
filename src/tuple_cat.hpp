/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _TUPLE_CAT_HPP
#define _TUPLE_CAT_HPP

#include <tuple>

namespace fp {
    template<typename...>
    struct tuple_cat;

    template<typename H, typename... T>
    struct tuple_cat<H, T...> {

        static inline auto cat(H h, T... t) -> decltype(std::tuple_cat(h, tuple_cat < T...>::cat(t...))) {
            return std::tuple_cat(h, tuple_cat < T...>::cat(t...));
        }
    };

    template<typename T>
    struct tuple_cat<T> {

        static inline T cat(T t) {
            return t;
        }
    };
}

#endif