/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _WHERE_SELECT_QUERY_HPP
#define _WHERE_SELECT_QUERY_HPP

#include "is_query.hpp"
#include "select_query.hpp"
#include "where_query.hpp"

#include <algorithm>            // for std::swap
#include <cstddef>              // for int
#include <string>               // for std::string, std::to_string
#include <vector>               // for std::vector

namespace fp {
    template<typename, typename> struct where_select_query;

    template<typename TDescriptor, int... Is, typename... Cs> struct is_query<where_select_query<select_query<TDescriptor, Is...>, where_query<TDescriptor, Cs...> > > {

        enum {
            value = true
        };
    };

    template<typename TDescriptor, int... Is, typename... Cs> struct where_select_query<select_query<TDescriptor, Is...>, where_query<TDescriptor, Cs...> > {
    public:
        typedef TDescriptor descriptor_type;
        typedef typename select_query<TDescriptor, Is...>::result_type result_type;
    protected:
        select_query<TDescriptor, Is...> m_select;
        where_query<TDescriptor, Cs...> m_where;
    public:
        where_select_query() : m_select(), m_where() {
        }

        where_select_query(select_query<TDescriptor, Is...> const & s, where_query<TDescriptor, Cs...> const & w) : m_select(s), m_where(w) {
        }

        where_select_query(where_select_query const & wsq) : m_select(wsq.m_select), m_where(wsq.m_where) {
        }

        where_select_query(where_select_query && wqs) : m_select(), m_where() {
            swap(*this, wqs);
        }

        friend void swap(where_select_query & l, where_select_query & r) {
            using std::swap;
            swap(l.m_select, r.m_select);
            swap(l.m_where, r.m_where);
        }

        template<int... Fs>
        friend bool evaluate(record<TDescriptor, Fs...> const & rec, where_select_query const & q) {
            return evaluate(rec, q.m_where);
        }

        template<int... Fs >
        friend result_type select(record<TDescriptor, Fs...> const & rec, where_select_query const & q) {
            return select(rec, q.m_select);
        }

        template<int... Fs >
        friend std::vector<result_type> apply(std::vector < record<TDescriptor, Fs...> > const & recs, where_select_query const & q) {
            std::vector<result_type> ret;
            for (record<TDescriptor, Fs...> const & cur : recs) {
                if (evaluate(cur, q.m_where)) {
                    ret.push_back(select(cur, q.m_select));
                }
            }
            return ret;
        }

        friend std::string to_string(where_select_query const & q) {
            using std::to_string;
            return to_string(q.m_select) + std::string(" ") + to_string(q.m_where);
        }
    };

    template<typename TDescriptor, int... Is, typename... Cs>
    inline where_select_query<select_query<TDescriptor, Is...>, where_query<TDescriptor, Cs...> > operator+(select_query<TDescriptor, Is...> const & s, where_query<TDescriptor, Cs...> const & w) {
        return where_select_query < select_query<TDescriptor, Is...>, where_query<TDescriptor, Cs...> >(s, w);
    }
}

#endif