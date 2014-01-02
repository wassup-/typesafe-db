/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _MYSQL_BASIC_ROW_HPP
#define _MYSQL_BASIC_ROW_HPP

#include "../lexical_cast.hpp"

#include <cstddef>              // for std::size_t
#include <utility>              // for std::swap
#include <mysql/mysql.h>        // for MYSQL_ROW

namespace fp {
    namespace mysql {

        struct basic_row {
        public:
            using this_type = basic_row;
            using size_type = std::size_t;
        protected:
            ::MYSQL_ROW _data;
            size_type _fields;
        public:

            CONSTEXPR basic_row() noexcept
            : _data(nullptr), _fields(0)
            { }

            CONSTEXPR explicit basic_row(::MYSQL_ROW d, size_type fields) noexcept
            : _data(d), _fields(fields)
            { }

            friend void swap(basic_row & l, basic_row & r) noexcept {
                using std::swap;
                swap(l._data, r._data);
            }

            CONSTEXPR size_type cols() const {
                return _fields;
            }

            CONSTEXPR char const * operator [](int i) const {
                return _data[i];
            }

            CONSTEXPR explicit operator bool() const {
                return (nullptr != _data);
            }

            template<int I, typename T>
            CONSTEXPR friend T get(basic_row const & r) {
                return lexical_cast<T>(r._data[I]);
            }
        };
    }
}

#endif