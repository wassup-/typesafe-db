#ifndef _WHERE_SELECT_QUERY_HPP
#define _WHERE_SELECT_QUERY_HPP

#include "select_query.hpp"
#include "where_query.hpp"

#include <vector>

namespace fp {
    template<typename, typename> struct where_select_query;

    template<typename TDescriptor, int... Is, typename... Cs> struct where_select_query<select_query<TDescriptor, Is...>, where_query<TDescriptor, Cs...> > {
    public:
        typedef TDescriptor descriptor_type;
        typedef typename TDescriptor::table::type table_type;
        typedef typename TDescriptor::record::type record_type;
        typedef typename select_query<TDescriptor, Is...>::result_type result_type;
    protected:
        select_query<TDescriptor, Is...> const m_select;
        where_query<TDescriptor, Cs...> const m_where;
    public:
        where_select_query(select_query<TDescriptor, Is...> const & s, where_query<TDescriptor, Cs...> const & w) : m_select(s), m_where(w) { }

        bool evaluate(record_type const & rec) const {
            return fp::evaluate(rec, m_where);
        }

        result_type select(record_type const & rec) const {
            return fp::select(rec, m_select);
        }

        std::vector<result_type> apply(std::vector<record_type> const & recs) const {
            std::vector<result_type> ret;
            for (auto const & cur : recs) {
                if (fp::evaluate(cur, m_where)) {
                    ret.push_back(fp::select(cur, m_select));
                }
            }
            return ret;
        }

        std::string to_string() const {
            return m_select.to_string() + std::string(" ") + m_where.to_string();
        }
    };

    template<typename TDescriptor, int... Is, typename... Cs>
    inline bool evaluate(typename TDescriptor::record_type const & r, where_select_query<select_query<TDescriptor, Is...>, where_query<TDescriptor, Cs...> > const & q) {
        return q.evaluate(r);
    }

    template<typename TDescriptor, int... Is, typename... Cs>
    inline auto select(typename TDescriptor::record_type const & r, where_select_query<select_query<TDescriptor, Is...>, where_query<TDescriptor, Cs...> > const & q) -> decltype(q.select(r)) {
        return q.select(r);
    }

    template<typename TDescriptor, int... Is, typename... Cs>
    inline where_select_query<select_query<TDescriptor, Is...>, where_query<TDescriptor, Cs...> > operator+(select_query<TDescriptor, Is...> const & s, where_query<TDescriptor, Cs...> const & w) {
        return where_select_query < select_query<TDescriptor, Is...>, where_query<TDescriptor, Cs...> >(s, w);
    }

    template<typename TDescriptor, int... Is, typename... Cs>
    inline auto query(std::vector<typename TDescriptor::record_type> const & r, where_select_query<select_query<TDescriptor, Is...>, where_query<TDescriptor, Cs...> > const & q) -> decltype(q.apply(r)) {
        return q.apply(r);
    }
}

#endif