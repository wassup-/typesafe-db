/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _QUERY_COMBINER_HPP
#define _QUERY_COMBINER_HPP

#include "impl/query_combiner_impl.hpp"

namespace fp {

    template<typename...>
    struct select_query;

    template<
        typename... LColumns,
        typename... RColumns,
        typename = mpl::enable_if_t<mpl::all_<is_column<LColumns>..., is_column<RColumns>...>>
    >
    constexpr inline typename impl::query_combiner_impl<select_query, LColumns..., RColumns...>::normal
    combine(const select_query<LColumns...>&, const select_query<RColumns...>&) {
        return { };
    }

    template<
        typename... LColumns,
        typename... RColumns,
        typename = mpl::enable_if_t<mpl::all_<is_column<LColumns>..., is_column<RColumns>...>>
    >
    constexpr inline typename impl::query_combiner_impl<select_query, LColumns..., RColumns...>::unique
    combine_unique(const select_query<LColumns...>&, const select_query<RColumns...>&) {
        return { };
    }
}

#endif
