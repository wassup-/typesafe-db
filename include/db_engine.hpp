/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _DB_ENGINE_HPP
#define _DB_ENGINE_HPP

#include "type_traits.hpp"

#include <utility>      // for std::forward

namespace fp {

    namespace detail {

        template<typename>
        struct is_engine : Bool<false> { };
    }

    template<typename T>
    struct is_engine : detail::is_engine<T> { };

    template<typename TEngine, typename TQuery>
    inline auto query(TEngine&& eng, TQuery&& qry)
    -> decltype(std::forward<TEngine>(eng).query(std::forward<TQuery>(qry))) {
        static_assert(is_engine<Unqualified<TEngine>>::value, "TEngine is not an engine");
        return std::forward<TEngine>(eng).query(std::forward<TQuery>(qry));
    }
}

#endif