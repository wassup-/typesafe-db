/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _WHERE_QUERY_HPP
#define _WHERE_QUERY_HPP

#include "impl/where_query_impl.hpp"

#include "call_with.hpp"
#include "is_query.hpp"
#include "tuple_cat.hpp"
#include "type_traits.hpp"      // for fp::enable_if, fp::enable_if_c
#include "where_clauses.hpp"

#include <algorithm>            // for std::swap
#include <string>               // for std::string, std::to_string
#include <vector>               // for std::vector

namespace fp {

    template<typename...>
    struct where_query;

    template<typename... TWhere>
    struct is_query<where_query<TWhere...>> : All<All<impl::is_where_clause<TWhere>...>, is_same<DescriptorOf<TWhere>...>> { };
    
    template<typename... TWhere>
    struct is_where_query<where_query<TWhere...>> : Bool<true> { };

    template<typename... TWhere>
    struct where_query {
        using descriptor_type = FirstTypeOf<DescriptorOf<TWhere>...>;
    protected:
        std::tuple<TWhere...> clauses_;
    public:
        where_query() = default;

        where_query(TWhere... clauses)
        : clauses_(std::move(clauses)...)
        { }

        where_query(const where_query&) = default;

        where_query(where_query&& wc) noexcept
        : clauses_()
        { swap(*this, wc); }

        friend void swap(where_query& l, where_query& r) noexcept {
            using std::swap;
            swap(l.clauses_, r.clauses_);
        }

        template<typename TRecord, EnableIf<is_record<Unqualified<TRecord>>> = _>
        friend bool evaluate(TRecord&& rec, const where_query& q) {
            bool(*eval_fn)(const TRecord&, TWhere&&...) =&impl::where_query_impl::evaluate;
            return call_function(eval_fn, q.clauses_, std::forward<TRecord>(rec));
        }

        template<typename TRecord, EnableIf<is_record<TRecord>> = _>
        friend std::vector<TRecord> evaluate(const std::vector<TRecord>& recs, const where_query& q) {
            std::vector<TRecord> ret;
            for(const TRecord& cur : recs) {
                if(evaluate(cur, q)) {
                    ret.push_back(cur);
                }
            }
            return ret;
        }
        
        template<typename TRecord, EnableIf<is_record<TRecord>> = _>
        friend std::vector<TRecord> query(const std::vector<TRecord>& rec, const where_query& q) {
            return evaluate(rec, q);
        }

        friend std::string to_string(const where_query& q) {
            std::string(*build_fn)(TWhere...) = &impl::where_query_impl::build_where_query<TWhere...>;
            return call_function(build_fn, q.clauses_);
        }
        
        template<typename T> 
        friend where_query<TWhere..., T> operator+(const where_query& q, T c) {
            return call_constructor<where_query<TWhere..., T>>(std::tuple_cat(q.clauses_, std::tuple<T>(c)));
        }
    };
    
    template<typename... TCondition>
    CONSTEXPR inline where_query<Unqualified<TCondition>...> where(TCondition&&... c) {
        return { std::forward<TCondition>(c)... };
    }
}

#endif