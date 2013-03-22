/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _DB_ENGINE_HPP
#define _DB_ENGINE_HPP

#include <string>
#include <vector>

namespace fp {

    template<typename TEngine> struct db_engine {

        template<typename TQuery >
        std::vector<typename TQuery::result_type > query(TQuery const & q) {
            return static_cast<TEngine *> (this)->query(q);
        }

        std::string last_query() const {
            return static_cast<TEngine const *> (this)->last_query();
        }
    };

    template<typename TEngine, typename TQuery>
    inline auto query(db_engine<TEngine> & eng, TQuery const & qry) -> decltype(eng.query(qry)) {
        return eng.query(qry);
    }
}

#endif