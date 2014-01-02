/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _WHERE_SELECT_QUERY_HPP
#define _WHERE_SELECT_QUERY_HPP

#include "is_query.hpp"
#include "select_query.hpp"
#include "stringutil.hpp"       // for stringutils::concatenate
#include "where_query.hpp"

#include <algorithm>            // for std::swap
#include <string>               // for std::string, std::to_string
#include <vector>               // for std::vector

namespace fp {
    template<typename, typename>
    struct where_select_query;

    template<typename TSelect, typename TWhere>
    struct is_query<where_select_query<TSelect, TWhere> > : All<is_select_query<TSelect>, is_where_query<TWhere>> { };
    
    template<typename TSelect, typename TWhere>
    struct is_select_query<where_select_query<TSelect, TWhere> > : is_select_query<TSelect> { };
    
    template<typename TSelect, typename TWhere>
    struct is_where_query<where_select_query<TSelect, TWhere> > : is_where_query<TWhere> { };

    template<typename TSelect, typename TWhere>
    struct where_select_query {
    public:
        
        template<typename TRecord>
        struct result_of {
            using type = Invoke<typename TSelect::template result_of<TRecord>>;
        };
    protected:
        TSelect _select;
        TWhere _where;
    public:
        where_select_query() = default;

        where_select_query(TSelect s, TWhere w)
        : _select(std::move(s)), _where(std::move(w))
        { }

        where_select_query(const where_select_query&) = default;

        where_select_query(where_select_query&& qry) noexcept
        : _select(), _where()
        { swap(*this, qry); }

        friend void swap(where_select_query& l, where_select_query& r) noexcept {
            using std::swap;
            swap(l._select, r._select);
            swap(l._where, r._where);
        }

        template<typename TRecord, EnableIf<is_record<Unqualified<TRecord>>> = _>
        friend bool evaluate(TRecord&& rec, const where_select_query& q) {
            return evaluate(std::forward<TRecord>(rec), q._where);
        }

        template<typename TRecord, EnableIf<is_record<TRecord>> = _>
        friend Invoke<result_of<Unqualified<TRecord>>> select(TRecord&& rec, const where_select_query& q) {
            return select(std::forward<TRecord>(rec), q._select);
        }

        template<typename TRecord, EnableIf<is_record<TRecord>> = _>
        friend std::vector<Invoke<result_of<TRecord>>> query(const std::vector<TRecord>& recs, const where_select_query& q) {
            std::vector<Invoke<result_of<TRecord>>> ret;
            for(const TRecord& cur : recs) {
                if (evaluate(cur, q._where)) {
                    ret.push_back(select(cur, q._select));
                }
            }
            return ret;
        }

        friend std::string to_string(const where_select_query& q) {
            using std::to_string;
            return stringutils::concatenate(to_string(q._select), " ", to_string(q._where));
        }
    };

    template<typename TSelect, typename TWhere, EnableIf<is_select_query<Unqualified<TSelect>>, is_where_query<Unqualified<TWhere>>> = _>
    CONSTEXPR inline where_select_query<Unqualified<TSelect>, Unqualified<TWhere>> operator+(TSelect&& s, TWhere&& w) {
        return { std::forward<TSelect>(s), std::forward<TWhere>(w) };
    }
}

#endif