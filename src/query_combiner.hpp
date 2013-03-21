/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _QUERY_COMBINER_HPP
#define _QUERY_COMBINER_HPP

#include "impl/query_combiner_impl.hpp"

namespace fp {
    template<int...> struct int_seq;
    template<typename, int...> struct select_query;

    template<typename TTable, int... L, int... R>
    typename impl::query_combiner_impl<TTable, int_seq<L...>, int_seq<R...> >::normal::type combine(select_query<TTable, L...>, select_query<TTable, R...>) {
        return typename impl::query_combiner_impl<TTable, int_seq<L...>, int_seq<R...> >::normal::type();
    }

    template<typename TTable, int... L, int... R>
    typename impl::query_combiner_impl<TTable, int_seq<L...>, int_seq<R...> >::unique::type combine_unique(select_query<TTable, L...>, select_query<TTable, R...>) {
        return typename impl::query_combiner_impl<TTable, int_seq<L...>, int_seq<R...> >::unique::type();
    }
}

#endif