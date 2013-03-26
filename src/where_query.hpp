/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _WHERE_QUERY_HPP
#define _WHERE_QUERY_HPP

#include "impl/where_query_impl.hpp"

#include "apply_tuple.hpp"
#include "is_query.hpp"
#include "tuple_cat.hpp"
#include "where_clauses.hpp"

#include <algorithm>            // for std::swap
#include <cstddef>              // for int
#include <string>               // for std::string
#include <type_traits>          // for std::enable_if
#include <vector>               // for std::vector

namespace fp {
    template<typename, typename...> struct where_query;

    template<typename TDescriptor, typename... TClauses> struct is_query<where_query<TDescriptor, TClauses...> > {

        enum {
            value = true
        };
    };
    
    template<typename TDescriptor> struct where_query<TDescriptor> {
        typedef TDescriptor descriptor_type;
        typedef typename TDescriptor::record::type result_type;
        
        template<typename TClause> friend where_query<TDescriptor, TClause> operator+(where_query<TDescriptor> const & q, TClause c) {
            return where_query<TDescriptor, TClause>(c);
        }
    };

    template<typename TDescriptor, typename... TClauses> struct where_query {
        typedef TDescriptor descriptor_type;
        typedef typename TDescriptor::record::type result_type;
    protected:
        std::tuple < TClauses...> m_clauses;
    public:
        where_query() : m_clauses() {
        }

        where_query(TClauses... clauses) : m_clauses(clauses...) {
        }

        where_query(where_query const & wc) : m_clauses(wc.m_clauses) {
        }

        where_query(where_query && wc) : m_clauses() {
            swap(*this, wc);
        }

        friend void swap(where_query & l, where_query & r) {
            using std::swap;
            swap(l.m_clauses, r.m_clauses);
        }

        template<int... Fs>
        friend bool evaluate(record<TDescriptor, Fs...> const & r, where_query const & q) {
            auto wrapper = wrap_fn(&impl::where_query_impl::evaluate<TDescriptor, Fs..., TClauses...>);
            return call_function(wrapper, q.m_clauses, r); //apply_tuple < std::tuple_size < std::tuple < TClauses...> >::value>::function::template apply < impl::clause_evaluator < record<TDescriptor, Fs...>, TClauses...> >(q.m_clauses);
        }

        template<int... Fs >
        friend std::vector < record<TDescriptor, Fs...> > evaluate(std::vector < record<TDescriptor, Fs...> > const & r, where_query const & q) {
            std::vector < record<TDescriptor, Fs...> > ret;
            for (record<TDescriptor, Fs...> const & cur : r) {
                if (evaluate(cur, q)) {
                    ret.push_back(cur);
                }
            }
            return ret;
        }
        
        template<int... Fs >
        friend std::vector < record<TDescriptor, Fs...> > query(std::vector < record<TDescriptor, Fs...> > const & r, where_query const & q) {
            return evaluate(r, q);
        }

        friend std::string to_string(where_query const & q) {
            auto wrapper = wrap_fn(&impl::where_query_impl::build_where_query<TDescriptor, TClauses...>);
            return call_function(wrapper, q.m_clauses);
        }
        
        template<typename TClause> 
        friend where_query<TDescriptor, TClauses..., TClause> operator+(where_query<TDescriptor, TClauses...> const & q, TClause c) {
            typedef where_query<TDescriptor, TClauses..., TClause> return_type;
            return call_constructor<return_type>(std::tuple_cat(q.m_clauses, std::tuple<TClause > (c)));
        }
    };

    template<typename TDescriptor, typename... TClauses, typename TClause>
    inline where_query<where_clauses::where_and<where_query<TDescriptor, TClauses...>, TClause> > operator&(where_query<TDescriptor, TClauses...> q, TClause c) {
        typedef where_clauses::where_and < where_query<TDescriptor, TClauses...>, TClause > clause_type;
        typedef where_query<clause_type> return_type;
        return return_type(clause_type(q, c));
    }
}

#endif