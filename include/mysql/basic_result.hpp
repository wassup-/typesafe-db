/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _MYSQL_BASIC_RESULT_HPP
#define _MYSQL_BASIC_RESULT_HPP

#include "basic_row.hpp"
#include "basic_context.hpp"
#include "basic_result_iterator.hpp"
#include "../core/non_copyable.hpp"

#include <cstddef>              // for std::size_t
#include <memory>               // for std::unique_ptr
#include <utility>              // for std::swap
#include <mysql/mysql.h>        // for MYSQL_RES, mysql_fetch_row, mysql_free_result, mysql_num_fields, mysql_num_rows, mysql_use_result

namespace fp { namespace mysql {

    class basic_result : non_copyable {
    public:
        using this_type = basic_result;
        using size_type = std::size_t;
        using row_type = basic_row;
        using iterator = result_iterator<this_type, row_type*>;
        using const_iterator = result_iterator<this_type, const row_type*>;

    public:
        basic_result(basic_context& ctx)
        : self_(::mysql_store_result(ctx.handle()), &::mysql_free_result)
        { }

        basic_result(basic_result&& res)
        : self_(nullptr, &::mysql_free_result)
        { swap(*this, res); }

        friend void swap(basic_result& l, basic_result& r) {
            using std::swap;
            swap(l.self_, r.self_);
        }

        explicit operator bool() const {
            return static_cast<bool>(self_);
        }

        size_type rows() const {
            return ::mysql_num_rows(self_.get());
        }

        size_type cols() const {
            return ::mysql_num_fields(self_.get());
        }

        row_type fetch_row() const {
            return row_type{ ::mysql_fetch_row(self_.get()), cols() };
        }

        iterator begin() {
            return iterator(*this, 0);
        }

        iterator end() {
            return iterator(*this, rows());
        }

    public:
        friend iterator begin(basic_result& res) {
            return res.begin();
        }

        friend iterator end(basic_result& res) {
            return res.end();
        }

    private:
        using resource_type = ::MYSQL_RES;
        std::unique_ptr<resource_type, decltype(&::mysql_free_result)> self_;
    };
} }

#endif