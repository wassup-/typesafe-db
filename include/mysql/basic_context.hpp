/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef MYSQL_BASIC_CONTEXT_HPP
#define MYSQL_BASIC_CONTEXT_HPP

#include "../core/non_copyable.hpp"

#include <memory>               // for std::unique_ptr
#include <utility>              // for std::swap

#include <mysql/mysql.h>        // for MYSQL

namespace fp
{

namespace mysql
{

class basic_engine;
class basic_result;

class basic_context : non_copyable
{
public:
  using this_type = basic_context;
  using native_handle = ::MYSQL;

protected:
  friend class basic_engine;
  friend class basic_result;

  std::unique_ptr<native_handle, decltype(&::mysql_close) > _context;

  explicit basic_context(native_handle* const ctx)
  : _context(ctx, &::mysql_close)
  { }

  inline native_handle* handle() const {
    return _context.get();
  }

  basic_context& operator=(native_handle* const ctx) {
    if (handle() != ctx) {
      _context.reset(ctx);
    }
    return *this;
  }

public:
  basic_context()
  : _context(::mysql_init(nullptr), &::mysql_close)
  { }

  basic_context(basic_context&& ctx)
  : _context(nullptr, &::mysql_close)
  { swap(*this, ctx); }

  friend void swap(basic_context& l, basic_context& r) {
    using std::swap;
    swap(l._context, r._context);
  }

  static basic_context * create() {
    native_handle* const ctx = ::mysql_init(nullptr);
    return (ctx) ? new basic_context(ctx) : 0;
  }

  explicit operator bool() const {
    return static_cast<bool>(_context);
  }

  operator native_handle*() const {
    return handle();
  }

  int query(const std::string& qry) {
    return ::mysql_query(handle(), qry.c_str());
  }
};

} // namespace mysql

} // namespace fp

#endif
