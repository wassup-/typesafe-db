/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _WHERE_UPDATE_QUERY_HPP
#define _WHERE_UPDATE_QUERY_HPP

#include "is_query.hpp"
#include "update_query.hpp"
#include "where_query.hpp"

#include <algorithm>            // for std::swap
#include <string>               // for std::string, std::to_string
#include <vector>               // for std::vector

namespace fp {
    template<typename, typename>
    struct where_update_query;

    template<typename TUpdate, typename TWhere>
    struct is_query<where_update_query<TUpdate, TWhere> > : All<is_update_query<TUpdate>, is_where_query<TWhere>> { };
    
    template<typename TUpdate, typename TWhere>
    struct is_update_query<where_update_query<TUpdate, TWhere> > : Bool<true> { };
    
    template<typename TUpdate, typename TWhere>
    struct is_where_query<where_update_query<TUpdate, TWhere> > : Bool<true> { };

    template<typename TUpdate, typename TWhere>
    struct where_update_query {
    public:
        
        template<typename TRecord>
        struct result_of {
            using type = Invoke<typename TUpdate::template result_of<TRecord>>;
        };
    protected:
        TUpdate _update;
        TWhere _where;
    public:

        where_update_query()
        : _update(), _where() {
        }

        where_update_query(TUpdate u, TWhere w)
        : _update(std::move(u)), _where(std::move(w)) {
        }

        where_update_query(where_update_query const &) = default;

        where_update_query(where_update_query && qry) noexcept
        : _update(), _where() {
            swap(*this, qry);
        }

        friend void swap(where_update_query & l, where_update_query & r) noexcept {
            using std::swap;
            swap(l._update, r._update);
            swap(l._where, r._where);
        }

        template<typename TRecord, EnableIf<is_record<Unqualified<TRecord>>> = _>
        friend bool evaluate(TRecord && rec, where_update_query const & q) {
            return evaluate(std::forward<TRecord>(rec), q._where);
        }

        template<typename TRecord, EnableIf<is_record<Unqualified<TRecord>>> = _>
        friend Invoke<result_of<Unqualified<TRecord>>> update(TRecord && rec, where_update_query const & q) {
            return update(std::forward<TRecord>(rec), q._update);
        }

        template<typename TRecord, EnableIf<is_record<TRecord>> = _>
        friend Invoke<result_of<TRecord>> update(std::vector<TRecord> & recs, where_update_query const & q) {
            typename result_of<TRecord>::type ret = 0;
            for (TRecord & cur : recs) {
                if (evaluate(cur, q._where)) {
                    ret += update(cur, q._update);
                }
            }
            return ret;
        }
        
        template<typename TRecord, EnableIf<is_record<TRecord>> = _>
        friend Invoke<result_of<TRecord>> query(std::vector<TRecord> & recs, where_update_query const & q) {
            return update(recs, q);
        }

        friend std::string to_string(where_update_query const & q) {
            using std::to_string;
            return to_string(q._update) + std::string(" ") + to_string(q._where);
        }
    };
    
    template<typename... Ms, typename... Cs>
    inline where_update_query<update_query<Ms...>, where_query<Cs...>> operator+(update_query<Ms...> const & u, where_query<Cs...> const & w) {
        return where_update_query<update_query<Ms...>, where_query<Cs...>>(u, w);
    }
}

#endif