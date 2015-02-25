/* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/.*/

#ifndef MYSQL_BASIC_ENGINE_HPP
#define MYSQL_BASIC_ENGINE_HPP

#include "basic_formatter.hpp"
#include "impl/basic_engine_impl.hpp"

#include "basic_context.hpp"
#include "basic_result.hpp"
#include "basic_row.hpp"
#include "../assert.hpp"
#include "../db_engine.hpp"     // for fp::is_engine
#include "../forward.hpp"       // for fix::forward
#include "../is_query.hpp"      // for fp::is_query
#include "../record.hpp"
#include "../type_traits.hpp"   // for fp::EnableIf, fp::DisableIf, fp::Invoke, fp::Unqualified

#include <algorithm>
#include <iterator>             // for std::back_inserter
#include <memory>               // for std::shared_ptr
#include <string>               // for std::string, std::to_string
#include <utility>              // for std::swap
#include <vector>               // for std::vector

#include <mysql/mysql.h>        // for MYSQL, MYSQL_RES

namespace fp
{

namespace mysql
{

class basic_engine
{
public:
  using default_record_type = record<>;
  using formatter = basic_formatter;

private:
  struct single_result_tag { };
  struct multiple_results_tag { };

public:
  constexpr static single_result_tag single_result { };
  constexpr static multiple_results_tag multiple_results { };

protected:
  std::shared_ptr<basic_context> _context;

public:
  basic_engine(const char* host, const char* name, const char* pass)
  : _context(basic_context::create())
  {
    if (_context) {
      MYSQL* res = ::mysql_real_connect(_context->handle(), host, name, pass, 0, 0, 0, 0);
      FP_ASSERT(res, "Unable to connect to MySQL server");
      *_context = res;
    }
  }

  basic_engine(const char* host, const char* name, const char* pass, const char* db)
  : _context(basic_context::create())
  {
    if (_context) {
      MYSQL* res = ::mysql_real_connect(_context->handle(), host, name, pass, db, 0, 0, 0);
      FP_ASSERT(res, "Unable to connect to MySQL server");
      *_context = res;
    }
  }

  basic_engine(const basic_engine&) = default;

  basic_engine(basic_engine&&) = default;

  friend void swap(basic_engine& l, basic_engine& r)
  {
    using std::swap;
    swap(l._context, r._context);
  }

  std::string errorstr() const
  {
    return ::mysql_error(_context->handle());
  }

  unsigned int error() const
  {
    return ::mysql_errno(_context->handle());
  }

  template<
    typename TQuery,
    typename TRecord = typename Unqualified<TQuery>::template result_of<default_record_type>,
    typename Container = std::vector<TRecord>,
    typename = mpl::enable_if_t<mpl::all_<is_query<Unqualified<TQuery>>, is_record<TRecord>>>
  >
  Container query(TQuery&& q, multiple_results_tag)
  {
    using std::to_string; using std::begin; using std::end;
    formatter fmt { };
    const std::string qry = to_string(fix::forward<TQuery>(q), fmt);
    if(0 != _context->query(qry.c_str())) {
      throw std::runtime_error("Could not query database");
    }
    mysql::basic_result res(*_context);
    if(res) {
      Container ret;
      ret.reserve(res.rows());
      std::transform(
        begin(res),
        end(res),
        std::back_inserter(ret),
        [](const basic_row& r) {
          return impl::make_record<TRecord>::make(r);
        }
      );
      return ret;
    }
    throw std::runtime_error("No valid context available");
  }

  template<
    typename TQuery,
    typename TRecord = typename Unqualified<TQuery>::template result_of<default_record_type>,
    typename Container = std::vector<TRecord>,
    typename = mpl::enable_if_t<mpl::all_<is_query<Unqualified<TQuery>>, is_record<TRecord>>>
  >
  Container query(TQuery&& q)
  {
    return query(q, multiple_results);
  }

  template<
    typename TQuery,
    typename TRecord = typename Unqualified<TQuery>::template result_of<default_record_type>,
    typename = mpl::enable_if_t<mpl::all_<is_query<Unqualified<TQuery>>, is_record<TRecord>>>
  >
  TRecord query(TQuery&& q, single_result_tag)
  {
    using std::to_string; using std::begin; using std::end;
    formatter fmt { };
    const std::string qry = to_string(fix::forward<TQuery>(q), fmt);
    if(0 != _context->query(qry.c_str())) {
      throw std::runtime_error("Could not query database");
    }
    mysql::basic_result res(*_context);
    if(res) {
      return impl::make_record<TRecord>::make(*begin(res));
    }
    throw std::runtime_error("No valid context available");
  }

  template<
    typename TQuery,
    typename TRecord = default_record_type,
    typename = mpl::disable_if_t<
      mpl::all_<
        is_query<Unqualified<TQuery>>,
        is_record<typename Unqualified<TQuery>::template result_of<TRecord>>
      >
    >
  >
  unsigned long long query(TQuery&& q){
    using std::to_string;
    formatter fmt { };
    const std::string qry = to_string(fix::forward<TQuery>(q), fmt);
    if (0 == ::mysql_query(_context->handle(), qry.c_str())) {
      return ::mysql_affected_rows(_context->handle());
    } else {
      return -1;
    }
  }
};

} // namespace mysql

namespace detail
{

template<>
struct is_engine<mysql::basic_engine> : meta::bool_<true> { };

} // namespace detail

} // namespace fp

#endif
