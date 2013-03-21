#ifndef _MYSQL_BASIC_RESULT_HPP
#define _MYSQL_BASIC_RESULT_HPP

#include "mysql_basic_row.hpp"
#include "mysql_result_iterator.hpp"

#include <mysql/mysql.h>

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
            basic_result(MYSQL * ctx) : m_context(ctx), m_res(mysql_use_result(ctx)) { }
            ~basic_result() {
                mysql_free_result(m_res);
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