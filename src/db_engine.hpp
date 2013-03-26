/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _DB_ENGINE_HPP
#define _DB_ENGINE_HPP

#include <algorithm>    // for std::swap
#include <string>       // for std::string
#include <vector>       // for std::vector

namespace fp {

    template<typename TEngine> struct db_engine {

        virtual ~db_engine() {
        }

        friend void swap(db_engine & l, db_engine & r) {
            using std::swap;
            swap(static_cast<TEngine &> (l), static_cast<TEngine &> (r));
        }

        std::string last_query() const {
            return static_cast<TEngine const *> (this)->last_query();
        }
    };

    template<typename TEngine, typename TQuery>
    inline auto query(db_engine<TEngine> & eng, TQuery && qry) -> decltype(static_cast<TEngine &>(eng).query(std::forward<TQuery>(qry))) {
        return static_cast<TEngine &>(eng).query(std::forward<TQuery > (qry));
    }
}

#endif