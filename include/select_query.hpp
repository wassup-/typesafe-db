/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _SELECT_QUERY_HPP
#define _SELECT_QUERY_HPP

#include "impl/select_query_impl.hpp"

#include "ce_tuple.hpp"
#include "forward.hpp"
#include "is_query.hpp"
#include "query_combiner.hpp"
#include "record.hpp"

#include <string>       // for std::string, std::to_string

namespace fp
{

template<typename...>
struct select_query;

template<typename... TColumns>
struct is_select_query<select_query<TColumns...> >
: mpl::all_<is_column<TColumns>...>
{ };

template<typename... TColumns>
struct is_query<select_query<TColumns...> >
: is_select_query<select_query<TColumns...> >
{ };

template<typename... TColumns>
struct select_query
{
public:
  template<typename TRecord>
  using result_of = typename TRecord::template rebind<TColumns...>;

public:
  constexpr select_query(TColumns... cols)
  : _columns(cols...)
  { }

  template<
    typename TRecord,
    typename = mpl::enable_if_t<is_record<TRecord> >
  >
  friend result_of<TRecord> select(const TRecord& rec, const select_query& q)
  {
    return { fp::get(rec, TColumns())... };
  }

  template<
    typename TContainer,
    typename TRecord = typename TContainer::value_type,
    typename = mpl::enable_if_t<is_record<TRecord> >
  >
  friend typename TContainer::template rebind<result_of<TRecord>>::type select(const TContainer& recs, const select_query& q)
  {
    using TReturnContainer = typename TContainer::template rebind<result_of<TRecord> >::type;
    TReturnContainer ret;
    ret.reserve(recs.size());
    for(const TRecord& cur : recs) {
      ret.push_back(select(cur, q));
    }
    return ret;
  }

  template<
    typename TContainer,
    typename TRecord = typename TContainer::value_type,
    typename = mpl::enable_if_t<is_record<TRecord> >
  >
  friend typename TContainer::template rebind<result_of<TRecord> >::type query(const TContainer& recs, const select_query& q)
  {
    return select(recs, q);
  }

  template<typename Formatter>
  friend std::string to_string(const select_query& q, Formatter& formatter)
  {
    std::string(*build_fn)(const TColumns&..., Formatter&) = &impl::select_query_impl<TColumns...>::build_select_query;
    return call_with(build_fn, q._columns, formatter);
  }
private:
  fp::ce_tuple<TColumns...> _columns;
};

template<
  typename... TColumns,
  typename = mpl::enable_if_t<mpl::all_<is_column<TColumns>...> >
>
constexpr inline select_query<TColumns...> select(TColumns... cols)
{
  return { cols... };
}

} // namespace fp

#endif
