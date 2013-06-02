/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef MYSQL_BASIC_ENGINE_HPP
#define MYSQL_BASIC_ENGINE_HPP

#include "impl/basic_engine_impl.hpp"

#include "../db_engine.hpp"     // for fp::is_engine
#include "../is_query.hpp"      // for fp::is_query
#include "basic_result.hpp"
#include "basic_row.hpp"
#include "basic_context.hpp"
#include "../type_traits.hpp"   // for fp::enable_if_c, fp::_not_c

#include <algorithm>            // for std::swap
#include <memory>               // for std::shared_ptr
#include <string>               // for std::string, std::to_string
#include <vector>               // for std::vector
#include <mysql/mysql.h>        // for MYSQL, MYSQL_RES

namespace fp {

    namespace mysql {

        struct basic_engine {
        public:
            typedef record<> default_record_type;
        protected:
            std::shared_ptr<basic_context> _context;
        public:

            basic_engine(char const * host, char const * name, char const * pass) : _context(basic_context::create()) {
                if (_context) {
                    ::mysql_real_connect(_context->handle(), host, name, pass, 0, 0, 0, 0);
                }
            }

            basic_engine(char const * host, char const * name, char const * pass, char const * db) : _context(basic_context::create()) {
                if (_context) {
                    if (::mysql_real_connect(_context->handle(), host, name, pass, 0, 0, 0, 0)) {
                        if (db) {
                            ::mysql_select_db(_context->handle(), db);
                        }
                    }
                }
            }

            basic_engine(basic_engine const &) = default;

            basic_engine(basic_engine &&) = default;

            friend void swap(basic_engine & l, basic_engine & r) {
                using std::swap;
                swap(l._context, r._context);
            }

            std::string errorstr() const {
                return ::mysql_error(_context->handle());
            }

            unsigned int error() const {
                return ::mysql_errno(_context->handle());
            }

            template<typename TQuery, typename TRecord = default_record_type, EnableIf < is_query<TQuery>, is_record < Invoke<typename TQuery::template result_of < TRecord >> >> = _ >
            std::vector < Invoke<typename TQuery::template result_of < TRecord >> > query(TQuery const & q) {
                using std::to_string;
                using record_type = Invoke<typename TQuery::template result_of < TRecord >>;
                std::string const qry = to_string(q);
                ::mysql_query(_context->handle(), qry.c_str());
                std::vector<record_type> ret;
                mysql::basic_result res(*_context);
                if (res) {
                    ret.reserve(res.rows());
                    mysql::basic_row row;
                    while ((row = res.fetch_row())) {
                        ret.push_back(impl::make_record<record_type>::make(row));
                    }
                }
                return ret;
            }

            template<typename TQuery, typename TRecord = default_record_type, DisableIf < is_query<TQuery>, is_record < Invoke<typename TQuery::template result_of < TRecord >> >> = _>
            unsigned long long query(TQuery const & q){
                using std::to_string;
                std::string const qry = to_string(q);
                if (0 == ::mysql_query(_context->handle(), qry.c_str())) {
                    return ::mysql_affected_rows(_context->handle());
                } else {
                    return -1;
                }
            }
        };
    }

    namespace detail {

        template<>
        struct is_engine<mysql::basic_engine> : std::true_type {
        };
    }
}

#endif