/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _MYSQL_ENGINE_HPP
#define _MYSQL_ENGINE_HPP

#include "db_engine.hpp"
#include "mysql_basic_result.hpp"
#include "mysql_basic_row.hpp"
#include "record.hpp"

#include <utility>
#include <vector>
#include <mysql/mysql.h>

namespace fp {
    namespace impl {
        template<int, typename, typename> struct make_record_impl;

        template<int I, typename TRecord, typename H, typename... T> struct make_record_impl<I, TRecord, type_seq<H, T...> > {
            template<typename... TArg>
            static TRecord make(mysql::basic_row const & r, TArg && ... arg) {
                return make_record_impl<I + 1, TRecord, type_seq<T...> >::make(r, std::forward<TArg>(arg)..., r.get<I, H>());
            }
        };

        template<int I, typename TRecord, typename H> struct make_record_impl<I, TRecord, type_seq<H> > {
            template<typename... TArg>
            static TRecord make(mysql::basic_row const & r, TArg && ... arg) {
                return TRecord(std::forward<TArg > (arg)..., r.get<I, H>());
            }
        };

        template<typename> struct make_record;

        template<typename TDescriptor, int... Is> struct make_record<record<TDescriptor, Is...> > {
            typedef record<TDescriptor, Is...> TRecord;

            static TRecord make(mysql::basic_row const & r) {
                return make_record_impl<0, TRecord, typename TRecord::types>::make(r);
            }
        };
    }

    struct mysql_engine : db_engine<mysql_engine> {
    protected:
        std::string m_last_query;
        MYSQL * m_context;
        MYSQL_RES * m_result;
    public:

        mysql_engine(char const * host, char const * name, char const * pass, char const * db = 0) : m_context(0) {
            m_context = mysql_init(m_context);
            if (m_context) {
                m_context = mysql_real_connect(m_context, host, name, pass, 0, 0, 0, 0);
                if (m_context && db) {
                    mysql_select_db(m_context, db);
                }
            }
        }

        ~mysql_engine() {
            mysql_close(m_context);
        }

        std::string last_query() const {
            return m_last_query;
        }

        template<typename TQuery > std::vector<typename TQuery::result_type > query(TQuery const & q) {
            std::string const qry = q.to_string();
            mysql_query(m_context, qry.c_str());
            std::vector<typename TQuery::result_type> ret;
            mysql::basic_result res(m_context);
            if (res) {
                ret.reserve(res.rows());
                mysql::basic_row row;
                while ((row = res.fetch_row())) {
                    ret.push_back(impl::make_record<typename TQuery::result_type>::make(row));
                }
            }
            m_last_query = qry;
            return ret;
        }
    };
}

#endif