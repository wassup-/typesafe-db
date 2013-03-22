/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _DROP_VALUES_HPP
#define _DROP_VALUES_HPP

#include "impl/drop_values_impl.hpp"

namespace fp {
    template<int...> struct int_seq;
    template<int, int...> struct drop_values;

    template<int C, int... I> struct drop_values {
        typedef typename impl::drop_values_impl<C, (C == sizeof...(I)), int_seq<>, int_seq < I...> >::type type;
    };

    template<int C, int... I> struct drop_values_or_empty {
        typedef typename impl::drop_values_impl<C, (C >= sizeof...(I)), int_seq<>, int_seq < I...> >::type type;
    };
}

#endif