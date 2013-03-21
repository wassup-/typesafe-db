#ifndef _QUERY_COMBINER_IMPL_HPP
#define _QUERY_COMBINER_IMPL_HPP

#include "../sorted_values.hpp"

namespace fp {
	template<int...> struct unique_values;
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
                typedef typename make_select_query<TTable, typename sorted_values<L..., R...>::type::template as<unique_values>::type::type>::type type;
            };
        };
    }
}

#endif