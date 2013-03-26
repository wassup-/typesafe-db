/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _INSERTION_SORT_HPP
#define _INSERTION_SORT_HPP

#include "impl/insertion_sort_impl.hpp"

#include "nth_value_of.hpp"
#include "skip_values.hpp"

#include <cstddef>              // for int

namespace fp {
    template<int...> struct int_seq;
    template<typename, typename, typename> struct insertion_sort;

    template<int... S, int... L, int... R> struct insertion_sort<int_seq<S...>, int_seq<L...>, int_seq<R...> > {

        enum {
            left = first_value_of < L...>::value,
            right = first_value_of < R...>::value,
        };

        using impl::insertion_sort_impl < (left < right), int_seq < S...>, int_seq < L...>, int_seq < R...> >::type;
    };

    template<int... S, int... L> struct insertion_sort<int_seq<S...>, int_seq<L...>, int_seq<> > : insertion_sort < int_seq < S..., L...>, int_seq<>, int_seq<> > {
    };

    template<int... S, int... R> struct insertion_sort<int_seq<S...>, int_seq<>, int_seq<R...> > : insertion_sort < int_seq < S..., R...>, int_seq<>, int_seq<> > {
    };

    template<int... S> struct insertion_sort<int_seq<S...>, int_seq<>, int_seq<> > {
        typedef int_seq < S...> type;
    };
}

#endif