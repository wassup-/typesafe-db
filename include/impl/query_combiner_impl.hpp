/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _QUERY_COMBINER_IMPL_HPP
#define _QUERY_COMBINER_IMPL_HPP

#include "../unique_types.hpp"

namespace fp {
    template<typename...>
    struct select_query;

    namespace impl {
        template<typename...>
        struct query_combiner_impl;

        template<typename>
        struct make_select_query;

        template<typename... TFields>
        struct make_select_query<type_sequence<TFields...> > {
            using type = select_query<TFields...>;
        };

        template<typename... TFields>
        struct query_combiner_impl {

            struct normal {
                using type = select_query<TFields...>;
            };

            struct unique {
                using type = Invoke<make_select_query<Invoke<unique_types<TFields...>>>>;
            };
        };
    }
}

#endif