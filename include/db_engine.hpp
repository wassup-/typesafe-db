/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _DB_ENGINE_HPP
#define _DB_ENGINE_HPP

#include "forward.hpp"      // for fix::forward
#include "is_query.hpp"     // for fp::is_query
#include "type_traits.hpp"  // for fp::EnableIf, fp::Unqualified

namespace fp {

    namespace detail {

        template<typename>
        struct is_engine : mpl::false_ { };
    }

    template<typename T>
    struct is_engine : detail::is_engine<T> { };

    template<typename TQuery>
    inline void expected_result(TQuery&& qry) {
        static_assert(is_query<Unqualified<TQuery>>::value, "TQuery is not a query");
    }

    template<typename Loader, typename Value>
    void prologue(Loader&, const Value&) { }
    
    template<typename Loader, typename Value>
    void epilogue(Loader&, const Value&) { }

    template<typename TEngine, typename TQuery>
    inline auto query(TEngine&& eng, TQuery&& qry)
    -> decltype(fix::forward<TEngine>(eng).query(fix::forward<TQuery>(qry))) {
        static_assert(is_engine<Unqualified<TEngine>>::value, "TEngine is not an engine");
        static_assert(is_query<Unqualified<TQuery>>::value, "TQuery is not a query");
        return fix::forward<TEngine>(eng).query(fix::forward<TQuery>(qry));
    }
}

#endif