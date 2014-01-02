/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _QUERY_COMBINER_HPP
#define _QUERY_COMBINER_HPP

#include "impl/query_combiner_impl.hpp"

namespace fp {
    
    template<typename...>
    struct select_query;

    template<typename... LFields, typename... RFields, EnableIf<is_field<LFields>..., is_field<RFields>...> = _>
    CONSTEXPR inline Invoke<typename impl::query_combiner_impl<LFields..., RFields...>::normal> combine(const select_query<LFields...>&, const select_query<RFields...>&) {
        return { };
    }

    template<typename... LFields, typename... RFields, EnableIf<is_field<LFields>..., is_field<RFields>...> = _>
    CONSTEXPR inline Invoke<typename impl::query_combiner_impl<LFields..., RFields...>::unique> combine_unique(const select_query<LFields...>&, const select_query<RFields...>&) {
        return { };
    }
}

#endif