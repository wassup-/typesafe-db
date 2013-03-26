/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _MYSQL_BASIC_RESULT_HPP
#define _MYSQL_BASIC_RESULT_HPP

#include "mysql_basic_row.hpp"
#include "mysql_result_iterator.hpp"

#include <algorithm>            // for std::swap
#include <mysql/mysql.h>        // for MYSQL, MYSQL_RES

namespace fp {
    namespace mysql {

        struct basic_result {
        public:
            typedef basic_result this_type;
            typedef result_iterator iterator;
            typedef result_iterator const_iterator;
        private:
        protected:
            MYSQL * m_context;
            MYSQL_RES * m_res;
        public:

            basic_result(MYSQL * ctx) : m_context(ctx), m_res(mysql_use_result(ctx)) {
            }

            ~basic_result() {
                mysql_free_result(m_res);
            }

            friend void swap(basic_result & l, basic_result & r) {
                using std::swap;
                swap(l.m_context, r.m_context);
                swap(l.m_res, r.m_res);
            }

            operator bool() const {
                return (0 != m_res);
            }

            int rows() const {
                return mysql_num_rows(m_res);
            }

            basic_row fetch_row() const {
                return basic_row(mysql_fetch_row(m_res));
            }

            iterator begin() {
                return iterator(*this);
            }

            iterator end() {
                return iterator(*this);
            }
        };
    }
}

#endif