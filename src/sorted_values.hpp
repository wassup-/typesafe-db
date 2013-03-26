/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _SORTED_VALUES_HPP
#define _SORTED_VALUES_HPP

#include "impl/sorted_values_impl.hpp"

#include <cstddef>              // for int

namespace fp {
    template<int...> struct int_seq;
    template<int...> struct sorted_values;

    template<int... V> struct sorted_values : impl::sorted_values_impl < int_seq<>, int_seq < V...>, int_seq<> > {
    };
}

#endif