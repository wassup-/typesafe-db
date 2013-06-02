/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _MYSQL_BASIC_RESULT_HPP
#define _MYSQL_BASIC_RESULT_HPP

#include "basic_row.hpp"
#include "basic_context.hpp"
#include "basic_result_iterator.hpp"
#include "../core/non_copyable.hpp"

#include <algorithm>            // for std::swap
#include <cstddef>              // for std::size_t
#include <memory>               // for std::unique_ptr
#include <mysql/mysql.h>        // for MYSQL, MYSQL_RES

namespace fp {
    namespace mysql {

        struct basic_result : non_copyable {
        public:
            typedef basic_result this_type;
            typedef std::size_t size_type;
            typedef result_iterator<basic_row *> iterator;
            typedef result_iterator<basic_row *> const_iterator;
        private:
            typedef typename ::MYSQL_RES resource_type;
        protected:
            std::unique_ptr<resource_type, decltype(&::mysql_free_result)> _res;
        public:

            basic_result(basic_context & ctx) : _res(::mysql_use_result(ctx.handle()), &::mysql_free_result) {
            }

            basic_result(basic_result && res) : _res(nullptr, &::mysql_free_result) {
                swap(*this, res);
            }

            friend void swap(basic_result & l, basic_result & r) {
                using std::swap;
                swap(l._res, r._res);
            }

            explicit operator bool() const {
                return static_cast<bool> (_res);
            }

            size_type rows() const {
                return ::mysql_num_rows(_res.get());
            }
            
            size_type cols() const {
                return ::mysql_num_fields(_res.get());
            }

            basic_row fetch_row() const {
                return basic_row(::mysql_fetch_row(_res.get()), ::mysql_num_fields(_res.get()));
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