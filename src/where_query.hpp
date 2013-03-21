/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _WHERE_QUERY_HPP
#define _WHERE_QUERY_HPP

#include "impl/where_query_impl.hpp"

#include "apply_tuple.hpp"
#include "is_query.hpp"
#include "tuple_cat.hpp"
#include "query_builder.hpp"
#include "where_clauses.hpp"

#include <string>
#include <type_traits>
#include <vector>

namespace fp {
    template<typename, typename...> struct where_query;
    
    template<typename TDescriptor, typename... TClauses> struct is_query<where_query<TDescriptor, TClauses...> > {
        enum { value = true };
    };

    
    
    template<typename TDescriptor, typename... TClauses> struct where_query {
        typedef TDescriptor descriptor_type;
        typedef typename TDescriptor::record::type result_type;
    protected:
        std::tuple < TClauses...> m_clauses;
    public:
        where_query(TClauses... clauses) : m_clauses(clauses...) { }
        where_query(where_query const & wc) : m_clauses(wc.m_clauses) { }

        std::tuple <TClauses...> const & clauses() const {
            return m_clauses;
        }

        template<int... Fs>
        bool evaluate(record<TDescriptor, Fs...> const & r) const {
            impl::clause_evaluator <record<TDescriptor, Fs...>, TClauses...> eval = apply_tuple<std::tuple_size<std::tuple<TClauses...> >::value>::constructor::template apply<impl::clause_evaluator<record<TDescriptor, Fs...>, TClauses...> >(m_clauses);
            return eval(r);
        }

        template<int... Fs>
        std::vector<record<TDescriptor, Fs...> > evaluate(std::vector<record<TDescriptor, Fs...> > const & r) const {
            std::vector<record<TDescriptor, Fs...> > ret;
            for(auto const & cur : r) {
                if (this->evaluate(cur)) {
                    ret.push_back(cur);
                }
            }
            return ret;
        }

        std::string to_string() const {
            query_builder qb;
            auto wrapper = wrap_call<decltype(impl::get_type_of(&query_builder::build_where_query<TDescriptor, TClauses...>))>(qb, &query_builder::build_where_query<TDescriptor, TClauses...>);
            return call_function(wrapper, m_clauses);
        }
    };

    template<typename TDescriptor, typename... TClauses, typename TClause>
    typename std::enable_if<(sizeof...(TClauses) > 0), where_query<TDescriptor, TClauses..., TClause> >::type operator+(where_query<TDescriptor, TClauses...> q, TClause c) {
        return apply_tuple<std::tuple_size<std::tuple<TClauses..., TClause> >::value>::constructor::template apply<where_query<TDescriptor, TClauses..., TClause> >(fp::tuple_cat<std::tuple<TClauses>..., std::tuple<TClause> >::cat(q.clauses(), std::tuple<TClause>(c)));
    }

    template<typename TDescriptor, typename... TClauses, typename TClause>
    typename std::enable_if<(sizeof...(TClauses) == 0), where_query<TDescriptor, TClauses..., TClause> >::type operator+(where_query<TDescriptor, TClauses...>, TClause c) {
        return where_query<TDescriptor, TClause > (c);
    }

    template<typename TDescriptor, typename... TClauses, typename TClause>
    where_query<where_clauses::where_and<where_query<TDescriptor, TClauses...>, TClause> > operator&(where_query<TDescriptor, TClauses...> q, TClause c) {
        return where_query<where_clauses::where_and<where_query<TDescriptor, TClauses...>, TClause> >(where_clauses::where_and<where_query<TDescriptor, TClauses...>, TClause >(q, c));
    }

    template<typename TDescriptor, typename... TClauses, int... Fs>
    auto evaluate(record<TDescriptor, Fs...> const & rec, where_query<TDescriptor, TClauses...> const & qry) -> decltype(qry.evaluate(rec)) {
        return qry.evaluate(rec);
    }

    template<typename TDescriptor, typename... TClauses, int... Fs>
    auto evaluate(std::vector<record<TDescriptor, Fs...> > const & recs, where_query<TDescriptor, TClauses...> const & qry) -> decltype(qry.evaluate(recs)) {
        return qry.evaluate(recs);
    }
}

#endif