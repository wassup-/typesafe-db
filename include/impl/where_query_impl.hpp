/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _WHERE_QUERY_IMPL_HPP
#define _WHERE_QUERY_IMPL_HPP

#include "../forward.hpp"
#include "../record.hpp"

#include <iostream>     // for std::ostream
#include <sstream>      // for std::ostringstream
#include <string>       // for std::string, std::to_string
#include <utility>      // for fix::forward

namespace fp
{

namespace impl
{

template<typename...>
struct where_query_impl;

template<typename...>
struct clause_evaluator;

template<typename H, typename... T>
struct clause_evaluator<H, T...>
{
protected:
  H head_;
  clause_evaluator<T...> tail_;

public:
  clause_evaluator(H h, T&&... t)
  : head_(h)
  , tail_(fix::forward<T>(t)...)
  { }

  template<typename... Fs>
  bool operator()(const record<Fs...>& r) const
  {
    return (head_(r) && tail_(r));
  }
};

template<typename H>
struct clause_evaluator<H>
{
protected:
  H head_;

public:
  clause_evaluator(H h)
  : head_(h)
  { }

  template<typename... Fs>
  bool operator()(const record<Fs...>& r) const {
    return head_(r);
  }
};

template<typename... Clauses>
struct where_query_impl
{
  template<typename Record>
  static bool evaluate(const Record& r, const Clauses&... clauses)
  {
    return clause_evaluator<Clauses...>{ clauses... }(r);
  }

  template<typename Formatter>
  static std::string build_where_query(Clauses... clauses, Formatter& formatter)
  {
    return stringutils::concatenate(
      "WHERE ",
      stringutils::implode(" AND ", formatter.to_string(clauses)...)
    );
  }
};

}

}

#endif
