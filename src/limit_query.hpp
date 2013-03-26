/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _LIMIT_QUERY_HPP
#define _LIMIT_QUERY_HPP

#include "is_query.hpp"

#include <algorithm>    // for std::swap
#include <cstddef>      // for int
#include <string>       // for std::string, std::to_string

namespace fp {
    template<typename> struct limit_query;

    template<typename TQuery> struct is_query<limit_query<TQuery> > {

        enum {
            value = true
        };
    };

    template<typename TQuery> struct limit_query {
    public:
        typedef typename TQuery::descriptor_type TDescriptor;
        typedef typename TQuery::result_type result_type;
    protected:
        TQuery m_query;
        int m_limit;
    public:

        limit_query(TQuery const & q, int l) : m_query(q), m_limit(l) {
        }

        limit_query(limit_query && q) : m_query(), m_limit() {
            swap(*this, q);
        }

        friend void swap(limit_query & l, limit_query & r) {
            using std::swap;
            swap(l.m_query, r.m_query);
            swap(l.m_limit, r.m_limit);
        }

        template<int... Fs>
        friend bool evaluate(record<TDescriptor, Fs...> const & rec, limit_query const & q) {
            return evaluate(rec, q.m_query);
        }

        template<int... Fs >
        friend result_type select(record<TDescriptor, Fs...> const & rec, limit_query const & q) {
            return select(rec, q.m_query);
        }

        template<int... Fs >
        friend std::vector<result_type> query(std::vector < record<TDescriptor, Fs...> > const & recs, limit_query const & q) {
            typedef record<TDescriptor, Fs...> record_type;
            std::vector<result_type> ret(q.m_limit);
            for (record_type const & cur : recs) {
                if (evaluate(cur, q.m_query)) {
                    ret.push_back(select(cur, q.m_query));
                    if (ret.size() == q.m_limit) {
                        break;
                    }
                }
            }
            return ret;
        }

        friend std::string to_string(limit_query const & q) {
            using std::to_string;
            return to_string(q.m_query) + std::string(" LIMIT ") + to_string(q.m_limit);
        }
    };

    template<typename TQuery>
    inline typename std::enable_if<is_query<TQuery>::value, limit_query<TQuery> >::type limit(TQuery const & q, int l) {
        return limit_query<TQuery > (q, l);
    }
}

#endif