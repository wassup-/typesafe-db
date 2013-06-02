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
        std::tuple<TWhere...> _clauses;
    public:
        where_query()
        : _clauses() {
        }

        where_query(TWhere... clauses)
        : _clauses(std::move(clauses)...) {
        }

        where_query(where_query const &) = default;

        where_query(where_query && wc) noexcept
        : _clauses() {
            swap(*this, wc);
        }

        friend void swap(where_query & l, where_query & r) noexcept {
            using std::swap;
            swap(l._clauses, r._clauses);
        }

        template<typename TRecord, EnableIf<is_record<TRecord>> = _>
        friend bool evaluate(TRecord const & rec, where_query const & q) {
            bool (*eval_fn)(TRecord const &, TWhere &&...) = &impl::where_query_impl::evaluate;
            return call_function(eval_fn, q._clauses, rec);
        }

        template<typename TRecord, EnableIf<is_record<TRecord>> = _>
        friend std::vector<TRecord> evaluate(std::vector<TRecord> const & recs, where_query const & q) {
            std::vector<TRecord> ret;
            for (TRecord const & cur : recs) {
                if (evaluate(cur, q)) {
                    ret.push_back(cur);
                }
            }
            return ret;
        }
        
        template<typename TRecord, EnableIf<is_record<TRecord>> = _>
        friend std::vector<TRecord> query(std::vector<TRecord> const & rec, where_query const & q) {
            return evaluate(rec, q);
        }

        friend std::string to_string(where_query const & q) {
            std::string(*build_fn)(TWhere...) = &impl::where_query_impl::build_where_query<TWhere...>;
            return call_function(build_fn, q._clauses);
        }
        
        template<typename T> 
        friend where_query<TWhere..., T> operator+(where_query const & q, T c) {
            return call_constructor<where_query<TWhere..., T> >(std::tuple_cat(q._clauses, std::tuple<T> (c)));
        }
    };
    
    template<typename... TConditions>
    inline where_query<TConditions...> where(TConditions... c) {
        return where_query<TConditions...>(std::move(c)...);
    }

    template<typename TDescriptor, typename... TWhere, typename T>
    inline where_query<where_clauses::where_and<where_query<TWhere...>, T> > operator&(where_query<TWhere...> q, T c) {
        typedef where_clauses::where_and<where_query<TWhere...>, T> clause_type;
        typedef where_query<clause_type> return_type;
        return return_type(clause_type(q, c));
    }
}

#endif