#ifndef _WHERE_SELECT_QUERY_HPP
#define _WHERE_SELECT_QUERY_HPP

#include "is_query.hpp"
#include "select_query.hpp"
#include "where_query.hpp"

#include <vector>

namespace fp {
    template<typename, typename> struct where_select_query;
    
    template<typename TDescriptor, int... Is, typename... Cs> struct is_query<where_select_query<select_query<TDescriptor, Is...>, where_query<TDescriptor, Cs...> > > {
        enum { value = true };
    };

    template<typename TDescriptor, int... Is, typename... Cs> struct where_select_query<select_query<TDescriptor, Is...>, where_query<TDescriptor, Cs...> > {
    public:
        typedef TDescriptor descriptor_type;
        typedef typename select_query<TDescriptor, Is...>::result_type result_type;
    protected:
        select_query<TDescriptor, Is...> const m_select;
        where_query<TDescriptor, Cs...> const m_where;
    public:
        where_select_query(select_query<TDescriptor, Is...> const & s, where_query<TDescriptor, Cs...> const & w) : m_select(s), m_where(w) { }

        template<int... Fs>
        bool evaluate(record<TDescriptor, Fs...> const & rec) const {
            return fp::evaluate(rec, m_where);
        }

        template<int... Fs>
        result_type select(record<TDescriptor, Fs...> const & rec) const {
            return fp::select(rec, m_select);
        }

        template<int... Fs>
        std::vector<result_type> apply(std::vector<record<TDescriptor, Fs...> > const & recs) const {
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

    template<typename TDescriptor, int... Is, typename... Cs, int... Fs>
    inline bool evaluate(record<TDescriptor, Fs...> const & r, where_select_query<select_query<TDescriptor, Is...>, where_query<TDescriptor, Cs...> > const & q) {
        return q.evaluate(r);
    }

    template<typename TDescriptor, int... Is, typename... Cs, int... Fs>
    inline auto select(record<TDescriptor, Fs...> const & r, where_select_query<select_query<TDescriptor, Is...>, where_query<TDescriptor, Cs...> > const & q) -> decltype(q.select(r)) {
        return q.select(r);
    }

    template<typename TDescriptor, int... Is, typename... Cs>
    inline where_select_query<select_query<TDescriptor, Is...>, where_query<TDescriptor, Cs...> > operator+(select_query<TDescriptor, Is...> const & s, where_query<TDescriptor, Cs...> const & w) {
        return where_select_query < select_query<TDescriptor, Is...>, where_query<TDescriptor, Cs...> >(s, w);
    }

    template<typename TDescriptor, int... Is, typename... Cs, int... Fs>
    inline auto query(std::vector<record<TDescriptor, Fs...> > const & r, where_select_query<select_query<TDescriptor, Is...>, where_query<TDescriptor, Cs...> > const & q) -> decltype(q.apply(r)) {
        return q.apply(r);
    }
}

#endif