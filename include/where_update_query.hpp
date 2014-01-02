/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _WHERE_UPDATE_QUERY_HPP
#define _WHERE_UPDATE_QUERY_HPP

#include "is_query.hpp"
#include "stringutil.hpp"       // for stringutils::concatenate
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
        TUpdate update_;
        TWhere where_;
    public:

        where_update_query() = default;

        where_update_query(TUpdate u, TWhere w)
        : update_(std::move(u)), where_(std::move(w))
        { }

        where_update_query(const where_update_query&) = default;

        where_update_query(where_update_query&& qry) noexcept
        : update_(), where_()
        { swap(*this, qry); }

        friend void swap(where_update_query& l, where_update_query& r) noexcept {
            using std::swap;
            swap(l.update_, r.update_);
            swap(l.where_, r.where_);
        }

        template<typename TRecord, EnableIf<is_record<Unqualified<TRecord>>> = _>
        friend bool evaluate(TRecord&& rec, const where_update_query& q) {
            return evaluate(std::forward<TRecord>(rec), q.where_);
        }

        template<typename TRecord, EnableIf<is_record<Unqualified<TRecord>>> = _>
        friend Invoke<result_of<Unqualified<TRecord>>> update(TRecord&& rec, const where_update_query& q) {
            return update(std::forward<TRecord>(rec), q.update_);
        }

        template<typename TRecord, EnableIf<is_record<TRecord>> = _>
        friend Invoke<result_of<TRecord>> update(std::vector<TRecord>& recs, const where_update_query& q) {
            typename result_of<TRecord>::type ret = 0;
            for(TRecord& cur : recs) {
                if(evaluate(cur, q.where_)) {
                    ret += update(cur, q.update_);
                }
            }
            return ret;
        }
        
        template<typename TRecord, EnableIf<is_record<TRecord>> = _>
        friend Invoke<result_of<TRecord>> query(std::vector<TRecord>& recs, const where_update_query& q) {
            return update(recs, q);
        }

        friend std::string to_string(const where_update_query& q) {
            using std::to_string;
            return stringutils::concatenate(to_string(q.update_), " ", to_string(q.where_));
        }
    };
    
    template<typename TUpdate, typename TWhere, EnableIf<is_update_query<Unqualified<TUpdate>>, is_where_query<Unqualified<TWhere>>> = _>
    CONSTEXPR inline where_update_query<Unqualified<TUpdate>, Unqualified<TWhere>> operator+(TUpdate&& u, TWhere&& w) {
        return { std::forward<TUpdate>(u), std::forward<TWhere>(w) };
    }
}

#endif