#ifndef _QUERY_COMBINER_IMPL_HPP
#define _QUERY_COMBINER_IMPL_HPP

#include "../unique_values.hpp"

#include <cstddef>              // for int

namespace fp {
    template<int...> struct int_seq;
    template<typename, int...> struct select_query;

    namespace impl {
        template<typename TTable, typename, typename> struct query_combiner_impl;

        template<typename TTable, typename> struct make_select_query;

        template<typename TTable, int... Is> struct make_select_query<TTable, int_seq<Is...> > {
            typedef select_query<TTable, Is...> type;
        };

        template<typename TTable, int... L, int... R> struct query_combiner_impl<TTable, int_seq<L...>, int_seq<R...> > {

            struct normal {
                typedef select_query<TTable, L..., R...> type;
            };

            struct unique {
                typedef typename make_select_query<TTable, typename unique_values < L..., R...>::type>::type type;
            };
        };
    }
}

#endif