/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _MYSQL_BASIC_ROW_HPP
#define _MYSQL_BASIC_ROW_HPP

#include "lexical_cast.hpp"

#include <mysql/mysql.h>

namespace fp {
    namespace mysql {

        struct basic_row {
        public:
            typedef basic_row this_type;
        protected:
            MYSQL_ROW m_data;
        public:

            basic_row() : m_data(0) {
            }

            explicit basic_row(MYSQL_ROW d) : m_data(d) {
            }

            ~basic_row() {
            }

            char const * operator [](int i) const {
                return m_data[i];
            }

            template<int I, typename T >
            T get() const {
                return lexical_cast<T > (m_data[I]);
            }

            operator bool() const {
                return (0 != m_data);
            }
        };
    }
}

#endif