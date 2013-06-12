/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _LIMIT_QUERY_HPP
#define _LIMIT_QUERY_HPP

#include "is_query.hpp"

#include <algorithm>    // for std::swap
#include <string>       // for std::string, std::to_string
#include <utility>      // for std::forward

namespace fp {
    template<typename>
    struct limit_query;

    template<typename TQuery>
    struct is_query<limit_query<TQuery> > : Bool<is_query<TQuery>::value> { };
    
    template<typename TQuery>
    struct is_limit_query<limit_query<TQuery> > : Bool<true> { };

    template<typename TQuery>
    struct limit_query {
    public:
        
        template<typename TRecord>
        struct result_of {
            using type = Invoke<typename TQuery::template result_of<TRecord>>;
        };
    protected:
        TQuery _query;
        int _limit;
    public:

        limit_query() {
        }

        limit_query(TQuery q, int l) : _query(std::move(q)), _limit(l) {
        }

        limit_query(limit_query const &) = default;

        limit_query(limit_query && q) noexcept : _query(), _limit() {
            swap(*this, q);
        }

        friend void swap(limit_query & l, limit_query & r) noexcept {
            using std::swap;
            swap(l._query, r._query);
            swap(l._limit, r._limit);
        }

        template<typename TRecord, EnableIf<is_record<Unqualified<TRecord>>> = _>
        friend bool evaluate(TRecord && rec, limit_query const & q) {
            return evaluate(rec, q._query);
        }

        template<typename TRecord, EnableIf<is_record<Unqualified<TRecord>>> = _>
        friend Invoke<result_of<Unqualified<TRecord>>> select(TRecord && rec, limit_query const & q) {
            return select(std::forward<TRecord>(rec), q._query);
        }

        template<typename TRecord, EnableIf<is_record<TRecord>> = _>
        friend std::vector<Invoke<result_of<TRecord>>> query(std::vector<TRecord> const & recs, limit_query const & q) {
            std::vector<Invoke<result_of<TRecord>>> ret(q._limit);
            for (TRecord const & cur : recs) {
                if (evaluate(cur, q._query)) {
                    ret.push_back(select(cur, q._query));
                    if (ret.size() == q._limit) {
                        break;
                    }
                }
            }
            return ret;
        }

        friend std::string to_string(limit_query const & q) {
            using std::to_string;
            return to_string(q._query) + std::string(" LIMIT ") + to_string(q._limit);
        }
    };

    template<typename TQuery, EnableIf<is_query<Unqualified<TQuery>>> = _>
    inline limit_query<Unqualified<TQuery>> limit(TQuery && q, int l) {
        return limit_query<Unqualified<TQuery>>(std::forward<TQuery>(q), l);
    }
}

#endif