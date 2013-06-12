/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _UNIQUE_VALUES_HPP
#define _UNIQUE_VALUES_HPP

#include "impl/unique_values_impl.hpp"

namespace fp {
    template<int...>
    struct int_seq;
    
    template<int...>
    struct unique_values;

    template<int H, int... T>
    struct unique_values<H, T...> : impl::unique_values_impl<int_seq<H>, int_seq<T...>> {
    };
}

#endif