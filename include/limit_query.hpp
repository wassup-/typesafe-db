/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _LIMIT_QUERY_HPP
#define _LIMIT_QUERY_HPP

#include "is_query.hpp"         // for fp::is_query
#include "record.hpp"
#include "stringutil.hpp"       // for stringutils::concatenate

#include <algorithm>            // for std::swap
#include <string>               // for std::string, std::to_string

namespace fp
{

template<typename /* Query */>
struct limit_query;

template<typename TQuery>
struct is_query<limit_query<TQuery> >
: is_query<TQuery>
{ };

template<typename TQuery>
struct is_limit_query<limit_query<TQuery> >
: meta::bool_<true>
{ };

template<typename TQuery>
struct limit_query
{
public:
  template<typename TRecord>
  using result_of = typename TQuery::template result_of<TRecord>;

protected:
  TQuery _query;
  int _limit;

public:
  constexpr limit_query(TQuery q, int l)
  : _query(q)
  , _limit(l)
  { }

  friend void swap(limit_query& l, limit_query& r) noexcept {
    using std::swap;
    swap(l._query, r._query);
    swap(l._limit, r._limit);
  }

  template<
    typename TRecord,
    typename = mpl::enable_if_t<is_record<TRecord>>
  >
  friend bool evaluate(const TRecord& rec, const limit_query& self) {
    return evaluate(rec, self._query);
  }

  template<
    typename TRecord,
    typename = mpl::enable_if_t<is_record<TRecord>>
  >
  friend result_of<TRecord> select(const TRecord& rec, const limit_query& self) {
    return select(rec, self._query);
  }

  template<
    typename TContainer,
    typename TRecord = typename TContainer::value_type,
    typename = mpl::enable_if_t<is_record<TRecord>>
  >
  friend TContainer query(const TContainer& recs, const limit_query& self) {
    TContainer ret;
    ret.reserve(self._limit);
    for(const TRecord& cur : recs) {
      if (evaluate(cur, self._query)) {
        ret.push_back(cur);
        if (ret.size() == self._limit) {
          break;
        }
      }
    }
    return ret;
  }

  template<typename Formatter>
  friend std::string to_string(const limit_query& self, Formatter& formatter)
  {
    return stringutils::concatenate(formatter.to_string(self._query), " LIMIT ", formatter.to_string(self._limit));
  }
};

template<
  typename TQuery,
  typename = mpl::enable_if_t<is_query<TQuery>>
>
constexpr inline limit_query<TQuery> limit(TQuery q, int l) {
  return { q, l };
}

} // namespace fp

#endif
