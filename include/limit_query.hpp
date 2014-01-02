/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _LIMIT_QUERY_HPP
#define _LIMIT_QUERY_HPP

#include "is_query.hpp"         // for fp::is_query
#include "stringutil.hpp"       // for stringutils::concatenate

#include <algorithm>            // for std::swap
#include <string>               // for std::string, std::to_string
#include <utility>              // for std::forward

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

        limit_query() = default;

        limit_query(TQuery q, int l)
        : _query(std::move(q)), _limit(l)
        { }

        limit_query(const limit_query&) = default;

        limit_query(limit_query&& q) noexcept
        : _query(), _limit(0)
        { swap(*this, q); }

        friend void swap(limit_query& l, limit_query& r) noexcept {
            using std::swap;
            swap(l._query, r._query);
            swap(l._limit, r._limit);
        }

        template<typename TRecord, EnableIf<is_record<Unqualified<TRecord>>> = _>
        friend bool evaluate(TRecord&& rec, const limit_query& q) {
            return evaluate(rec, q._query);
        }

        template<typename TRecord, EnableIf<is_record<Unqualified<TRecord>>> = _>
        friend Invoke<result_of<Unqualified<TRecord>>> select(TRecord&& rec, const limit_query& q) {
            return select(std::forward<TRecord>(rec), q._query);
        }

        template<typename TRecord, EnableIf<is_record<TRecord>> = _>
        friend std::vector<Invoke<result_of<TRecord>>> query(const std::vector<TRecord>& recs, const limit_query& q) {
            std::vector<Invoke<result_of<TRecord>>> ret(q._limit);
            for (const TRecord& cur : recs) {
                if (evaluate(cur, q._query)) {
                    ret.push_back(select(cur, q._query));
                    if (ret.size() == q._limit) {
                        break;
                    }
                }
            }
            return ret;
        }

        friend std::string to_string(const limit_query& q) {
            using std::to_string;
            return stringutils::concatenate(to_string(q._query), " LIMIT ", to_string(q._limit));
        }
    };

    template<typename TQuery, EnableIf<is_query<Unqualified<TQuery>>> = _>
    CONSTEXPR inline limit_query<Unqualified<TQuery>> limit(TQuery&& q, int l) {
        return { std::forward<TQuery>(q), l };
    }
}

#endif