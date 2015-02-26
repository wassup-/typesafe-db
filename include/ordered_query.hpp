/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _ORDERED_QUERY_HPP
#define _ORDERED_QUERY_HPP

#include "impl/ordered_query_impl.hpp"

#include "forward.hpp"
#include "is_query.hpp"
#include "record.hpp"
#include "stringutil.hpp"       // for stringutils::concatenate
#include "type_traits.hpp"      // for EnableIf

#include <algorithm>            // for std::swap, std::sort
#include <string>               // for std::string, std::to_string
#include <utility>              // for fix::forward

namespace fp
{

template<typename, typename>
struct ordered_query;

template<typename TQuery, typename TColumn>
struct is_ordered_query<ordered_query<TQuery, TColumn> >
: mpl::all_<is_query<TQuery>, is_column<TColumn> >
{ };

template<typename TQuery, typename TColumn>
struct is_query<ordered_query<TQuery, TColumn> >
: is_ordered_query<ordered_query<TQuery, TColumn> >
{ };

enum class ordering_e
{
  ascending = 0,
  descending = 1
};

constexpr ordering_e ascending = ordering_e::ascending;
constexpr ordering_e descending = ordering_e::descending;

template<typename TQuery, typename TColumn>
struct ordered_query
{
public:
  template<typename TRecord>
  using result_of = typename TQuery::template result_of<TRecord>;

public:
  ordered_query(TQuery q, TColumn c, ordering_e o)
  : _query(q)
  , _column(c)
  , _order(o)
  { }

  friend void swap(ordered_query& l, ordered_query& r) noexcept
  {
    using std::swap;
    swap(l._query, r._query);
    swap(l._order, r._order);
  }

  template<
    typename TContainer,
    typename TRecord = typename TContainer::value_type,
    typename = mpl::enable_if_t<is_record<TRecord> >
  >
  friend TContainer query(TContainer recs, const ordered_query& self)
  {
    using ascending_sorter = impl::ordered_query::ascending_sorter<TRecord, TColumn>;
    using descending_sorter = impl::ordered_query::descending_sorter<TRecord, TColumn>;

    switch(self._order)
    {
      case ascending:
        std::sort(begin(recs), end(recs), ascending_sorter{ });
        break;
      case descending:
        std::sort(begin(recs), end(recs), descending_sorter{ });
        break;
    }
    return recs;
  }

  template<typename Formatter>
  static std::string ordering_to_string(const ordered_query& q, Formatter& formatter, std::true_type)
  {
    return stringutils::concatenate(", ", formatter.to_string(q._column), " ", impl::ordered_query::ORDERINGS[static_cast<int>(q._order)]);
  }

  template<typename Formatter>
  static std::string ordering_to_string(const ordered_query& q, Formatter& formatter, std::false_type)
  {
    return stringutils::concatenate(" ORDER BY ", formatter.to_string(q._column), " ", impl::ordered_query::ORDERINGS[static_cast<int>(q._order)]);
  }

  template<typename Formatter>
  friend std::string to_string(const ordered_query& self, Formatter& formatter)
  {
    const std::string ordering = ordering_to_string(self, formatter, is_ordered_query<TQuery>{});
    return stringutils::concatenate(formatter.to_string(self._query), ordering);
  }

private:
  TQuery _query;
  TColumn _column;
  ordering_e _order;
};

/**
 * Applies absolute ordering to the result query
 * @param q query to apply absolute ordering to
 * @param f field on which to apply absolute ordering
 * @return ordered_query<TQuery, TColumn>
 */
template<
  typename TQuery,
  typename TColumn,
  typename = mpl::enable_if_t<mpl::all_<is_query<TQuery>, is_column<TColumn> > >
>
constexpr inline ordered_query<TQuery, TColumn> order(TQuery q, TColumn c, ordering_e o = ordering_e::ascending)
{
  return { q, c, o };
}

}

#endif
