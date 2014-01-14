/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _LIMIT_QUERY_HPP
#define _LIMIT_QUERY_HPP

#include "forward.hpp"
#include "is_query.hpp"         // for fp::is_query
#include "record.hpp"
#include "stringutil.hpp"       // for stringutils::concatenate

#include <algorithm>            // for std::swap
#include <string>               // for std::string, std::to_string
#include <utility>              // for fix::forward

namespace fp {

    template<typename /* Query */>
    struct limit_query;

    template<typename TQuery>
    struct is_query<limit_query<TQuery> > : is_query<TQuery> { };
    
    template<typename TQuery>
    struct is_limit_query<limit_query<TQuery> > : Bool<true> { };

    template<typename TQuery>
    struct limit_query {
    public:
        
        template<typename TRecord>
        struct result_of : identity<Invoke<typename TQuery::template result_of<TRecord>>> { };
    protected:
        TQuery _query;
        int _limit;
    public:

        constexpr limit_query(TQuery q, int l)
        : _query(q), _limit(l)
        { }

        friend void swap(limit_query& l, limit_query& r) noexcept {
            using std::swap;
            swap(l._query, r._query);
            swap(l._limit, r._limit);
        }

        template<
            typename TRecord,
            EnableIf<
                is_record<TRecord>
            > = _
        >
        friend bool evaluate(const TRecord& rec, const limit_query& q) {
            return evaluate(rec, q._query);
        }

        template<
            typename TRecord,
            EnableIf<
                is_record<TRecord>
            > = _
        >
        friend Invoke<result_of<TRecord>> select(const TRecord& rec, const limit_query& q) {
            return select(rec, q._query);
        }

        template<
            typename TContainer,
            typename TRecord = typename TContainer::value_type,
            EnableIf<
                is_record<TRecord>
            > = _
        >
        friend TContainer query(const TContainer& recs, const limit_query& q) {
            TContainer ret;
            ret.reserve(q._limit);
            for(const TRecord& cur : recs) {
                if (evaluate(cur, q._query)) {
                    ret.push_back(cur);
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

    template<
        typename TQuery,
        EnableIf<
            is_query<TQuery>
        > = _
    >
    constexpr inline limit_query<TQuery> limit(TQuery q, int l) {
        return { q, l };
    }
}

#endif