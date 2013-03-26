/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _WHERE_UPDATE_QUERY_HPP
#define _WHERE_UPDATE_QUERY_HPP

#include "is_query.hpp"
#include "update_query.hpp"
#include "where_query.hpp"

#include <algorithm>            // for std::swap
#include <cstddef>              // for int
#include <string>               // for std::string, std::to_string
#include <vector>               // for std::vector

namespace fp {
    template<typename, typename> struct where_update_query;

    template<typename TDescriptor, typename... Ms, typename... Cs>
    struct is_query<where_update_query<update_query<TDescriptor, Ms...>, where_query<TDescriptor, Cs...> > > {

        enum {
            value = true
        };
    };

    template<typename TDescriptor, typename... Ms, typename... Cs>
    struct where_update_query<update_query<TDescriptor, Ms...>, where_query<TDescriptor, Cs...> > {
    public:
        typedef TDescriptor descriptor_type;
        typedef typename update_query<TDescriptor, Ms...>::result_type result_type;
    protected:
        update_query<TDescriptor, Ms...> m_update;
        where_query<TDescriptor, Cs...> m_where;
    public:

        where_update_query() : m_update(), m_where() {
        }

        where_update_query(update_query<TDescriptor, Ms...> const & u, where_query<TDescriptor, Cs...> const & w) : m_update(u), m_where(w) {
        }

        where_update_query(where_update_query const & wsq) : m_update(wsq.m_update), m_where(wsq.m_where) {
        }

        where_update_query(where_update_query && wqs) : m_update(), m_where() {
            swap(*this, wqs);
        }

        friend void swap(where_update_query & l, where_update_query & r) {
            using std::swap;
            swap(l.m_update, r.m_update);
            swap(l.m_where, r.m_where);
        }

        template<int... Fs>
        friend bool evaluate(record<TDescriptor, Fs...> const & rec, where_update_query const & q) {
            return evaluate(rec, q.m_where);
        }

        template<int... Fs >
        friend result_type update(record<TDescriptor, Fs...> & rec, where_update_query const & q) {
            return update(rec, q.m_update);
        }

        template<int... Fs >
        friend result_type update(std::vector < record<TDescriptor, Fs...> > & recs, where_update_query const & q) {
            result_type ret = 0;
            for (record<TDescriptor, Fs...> & cur : recs) {
                if (evaluate(cur, q.m_where)) {
                    ret += update(cur, q.m_update);
                }
            }
            return ret;
        }

        friend std::string to_string(where_update_query const & q) {
            using std::to_string;
            return to_string(q.m_update) + std::string(" ") + to_string(q.m_where);
        }
    };
    
    template<typename TDescriptor, typename... Ms, typename... Cs>
    inline where_update_query<update_query<TDescriptor, Ms...>, where_query<TDescriptor, Cs...> > operator+(update_query<TDescriptor, Ms...> const & u, where_query<TDescriptor, Cs...> const & w) {
        return where_update_query<update_query<TDescriptor, Ms...>, where_query<TDescriptor, Cs...> >(u, w);
    }
}

#endif