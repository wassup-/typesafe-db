/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _WHERE_UPDATE_QUERY_HPP
#define _WHERE_UPDATE_QUERY_HPP

#include "forward.hpp"
#include "is_query.hpp"
#include "stringutil.hpp"       // for stringutils::concatenate
#include "update_query.hpp"
#include "where_query.hpp"

#include <algorithm>            // for std::swap
#include <string>               // for std::string, std::to_string

namespace fp
{

template<typename /* Update */, typename /* Where */>
struct where_update_query;

template<typename TUpdate, typename TWhere>
struct is_query<where_update_query<TUpdate, TWhere> > : mpl::all_<is_update_query<TUpdate>, is_where_query<TWhere>> { };

template<typename TUpdate, typename TWhere>
struct is_update_query<where_update_query<TUpdate, TWhere> > : is_update_query<TUpdate> { };

template<typename TUpdate, typename TWhere>
struct is_where_query<where_update_query<TUpdate, TWhere> > : is_where_query<TWhere> { };

template<typename TUpdate, typename TWhere>
struct where_update_query
{
public:
  template<typename TRecord>
  using result_of = typename TUpdate::template result_of<TRecord>;

public:
  constexpr where_update_query(TUpdate u, TWhere w)
  : update_(u), where_(w)
  { }

public:
  friend void swap(where_update_query& l, where_update_query& r) noexcept {
    using std::swap;
    swap(l.update_, r.update_);
    swap(l.where_, r.where_);
  }

  template<typename TRecord, typename = mpl::enable_if_t<is_record<Unqualified<TRecord>>>>
  friend bool evaluate(TRecord&& rec, const where_update_query& q) {
    return evaluate(fix::forward<TRecord>(rec), q.where_);
  }

  template<typename TRecord, typename = mpl::enable_if_t<is_record<Unqualified<TRecord>>>>
  friend result_of<Unqualified<TRecord>> update(TRecord&& rec, const where_update_query& q) {
    return update(fix::forward<TRecord>(rec), q.update_);
  }

  template<
    typename TContainer,
    typename TRecord = typename TContainer::value_type,
    typename = mpl::enable_if_t<is_record<TRecord>>
  >
  friend result_of<TRecord> update(TContainer& recs, const where_update_query& q) {
    result_of<TRecord> ret = 0;
    for(TRecord& cur : recs) {
      if(evaluate(cur, q.where_)) {
        ret += update(cur, q.update_);
      }
    }
    return ret;
  }

  template<
    typename TContainer,
    typename TRecord = typename TContainer::value_type,
    typename = mpl::enable_if_t<is_record<TRecord>>
  >
  friend result_of<TRecord> query(TContainer& recs, const where_update_query& q) {
    return update(recs, q);
  }

  template<typename Formatter>
  friend std::string to_string(const where_update_query& q, Formatter& formatter)
  {
    return stringutils::concatenate(formatter.to_string(q.update_), " ", formatter.to_string(q.where_));
  }

private:
  TUpdate update_;
  TWhere where_;
};

template<
  typename TUpdate,
  typename TWhere,
  typename = mpl::enable_if_t<mpl::all_<is_update_query<Unqualified<TUpdate>>, is_where_query<Unqualified<TWhere>>>>
>
constexpr inline where_update_query<Unqualified<TUpdate>, Unqualified<TWhere>> operator+(TUpdate&& u, TWhere&& w) {
  return { fix::forward<TUpdate>(u), fix::forward<TWhere>(w) };
}

}

#endif
