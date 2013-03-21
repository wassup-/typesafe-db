#ifndef _WHERE_QUERY_HPP
#define _WHERE_QUERY_HPP

#include "apply_tuple.hpp"
#include "tuple_cat.hpp"
#include "query_builder.hpp"
#include "where_clauses.hpp"

#include <algorithm>
#include <string>
#include <type_traits>
#include <vector>

namespace fp {
    template<typename, typename...> struct where_query;

    template<typename Fn> Fn get_type_of(Fn);

    template<typename, typename...> struct clause_evaluator;

    template<typename TRecord, typename H, typename... T> struct clause_evaluator<TRecord, H, T...> {
    protected:
        H m_head;
        clause_evaluator <TRecord, T...> m_tail;
    public:
        clause_evaluator(H h, T && ... t) : m_head(h), m_tail(std::forward<T> (t)...) { }

        bool operator()(TRecord const & r) const {
            return (m_head(r) && m_tail(r));
        }
    };

    template<typename TRecord, typename H> struct clause_evaluator<TRecord, H> {
    protected:
        H m_head;
    public:

        clause_evaluator(H h) : m_head(h) { }

        bool operator()(TRecord const & r) const {
            return m_head(r);
        }
    };

    template<typename TDescriptor, typename... TClauses> struct where_query {
        typedef TDescriptor descriptor_type;
        typedef typename TDescriptor::table::type table_type;
        typedef typename TDescriptor::record::type record_type;
        typedef record_type result_type;
    protected:
        std::tuple < TClauses...> m_clauses;
    public:
        where_query(TClauses... clauses) : m_clauses(clauses...) { }
        where_query(where_query const & wc) : m_clauses(wc.m_clauses) { }

        std::tuple <TClauses...> const & clauses() const {
            return m_clauses;
        }

        bool evaluate(record_type const & r) const {
            clause_evaluator <record_type, TClauses...> eval = apply_tuple<std::tuple_size<std::tuple<TClauses...> >::value>::constructor::template apply<clause_evaluator<record_type, TClauses...> >(m_clauses);
            return eval(r);
        }

        std::vector<record_type> evaluate(std::vector<record_type> const & r) const {
            std::vector<record_type> ret;
            for (auto const & cur : r) {
                if (this->evaluate(cur)) {
                    ret.push_back(cur);
                }
            }
            return ret;
        }

        std::string to_string() const {
            query_builder qb;
            auto wrapper = wrap_call<decltype(get_type_of(&query_builder::build_where_query<TDescriptor, TClauses...>))>(qb, &query_builder::build_where_query<TDescriptor, TClauses...>);
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

    template<typename TDescriptor, typename... TClauses>
    auto evaluate(typename TDescriptor::record_type const & rec, where_query<TDescriptor, TClauses...> const & qry) -> decltype(qry.evaluate(rec)) {
        return qry.evaluate(rec);
    }

    template<typename TDescriptor, typename... TClauses>
    auto evaluate(std::vector<typename TDescriptor::record_type> const & recs, where_query<TDescriptor, TClauses...> const & qry) -> decltype(qry.evaluate(recs)) {
        return qry.evaluate(recs);
    }
}

#endif