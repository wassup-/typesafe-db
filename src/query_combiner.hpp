/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _QUERY_COMBINER_HPP
#define _QUERY_COMBINER_HPP

#include "sorted_values.hpp"

namespace fp {
    template<int...> struct int_seq;
    template<typename...> struct type_seq;
    template<typename, int...> struct select_query;
    template<int...> struct unique_values;

    namespace impl {
        template<typename TTable, typename, typename> struct query_combiner;

        template<typename TTable, typename> struct make_select_query;
        template<typename TTable, int... Is> struct make_select_query<TTable, int_seq<Is...> > {
            typedef select_query<TTable, Is...> type;
        };

        template<typename TTable, int... L, int... R> struct query_combiner<TTable, int_seq<L...>, int_seq<R...> > {
            struct normal {
                typedef select_query<TTable, L..., R...> type;
            };
            struct unique {
                typedef typename make_select_query<TTable, typename sorted_values<L..., R...>::type::template as<unique_values>::type::type>::type type;
            };
        };
    }

    template<typename TTable, int... L, int... R>
    typename impl::query_combiner<TTable, int_seq<L...>, int_seq<R...> >::normal::type combine(select_query<TTable, L...>, select_query<TTable, R...>) {
        return typename impl::query_combiner<TTable, int_seq<L...>, int_seq<R...> >::normal::type();
    }

    template<typename TTable, int... L, int... R>
    typename impl::query_combiner<TTable, int_seq<L...>, int_seq<R...> >::unique::type combine_unique(select_query<TTable, L...>, select_query<TTable, R...>) {
        return typename impl::query_combiner<TTable, int_seq<L...>, int_seq<R...> >::unique::type();
    }
}

#endif