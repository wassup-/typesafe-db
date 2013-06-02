/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _MYSQL_BASIC_ROW_HPP
#define _MYSQL_BASIC_ROW_HPP

#include "../lexical_cast.hpp"

#include <algorithm>            // for std::swap
#include <cstddef>              // for std::size_t
#include <mysql/mysql.h>        // for MYSQL_ROW

namespace fp {
    namespace mysql {

        struct basic_row {
        public:
            typedef basic_row this_type;
            typedef std::size_t size_type;
        protected:
            ::MYSQL_ROW _data;
            size_type _fields;
        public:

            constexpr basic_row() noexcept : _data(nullptr), _fields(0) {
            }

            constexpr explicit basic_row(::MYSQL_ROW d, size_type fields) noexcept : _data(d), _fields(fields) {
            }

            friend void swap(basic_row & l, basic_row & r) noexcept {
                using std::swap;
                swap(l._data, r._data);
            }

            constexpr size_type cols() const {
                return _fields;
            }

            constexpr char const * operator [](int i) const {
                return _data[i];
            }

            constexpr explicit operator bool() const {
                return (nullptr != _data);
            }

            template<int I, typename T>
            constexpr friend T get(basic_row const & r) {
                return lexical_cast<T > (r._data[I]);
            }
        };
    }
}

#endif