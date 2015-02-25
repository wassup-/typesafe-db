/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _RECORD_HPP
#define _RECORD_HPP

#include "config.hpp"
#include "column.hpp"           // for fp::is_column
#include "meta.hpp"
#include "type_traits.hpp"      // for fp::EnableIf, fp::DisableIf

#include <stdexcept>

namespace fp
{

template<typename... /* Columns */>
struct record;

template<typename>
struct is_record
: meta::bool_<false> { };

template<typename... TColumns>
struct is_record<record<TColumns...> >
: meta::all_of<
    meta::list<TColumns...>,
    meta::quote<is_column> >
{ };

template<>
struct record<>
{
  using this_type = record;

  template<typename... TOther>
  using rebind = record<TOther...>;
};

template<typename... Columns>
struct record
{
public:
  using this_type = record;

  template<typename... TOther>
  using rebind = record<TOther...>;

  template<std::size_t Idx>
  using nth_type = meta::list_element_c<
                     Idx,
                     meta::list<Columns...> >;

  template<std::size_t Idx>
  using nth_value_type = typename nth_type<Idx>::value_type;

public:
  record(typename Columns::value_type... x)
  : values_(x...)
  { }

  constexpr static std::size_t size()
  { return sizeof...(Columns); }

  template<std::size_t Idx>
  nth_value_type<Idx>& get()
  { return std::get<Idx>(values_); }

  template<std::size_t Idx>
  const nth_value_type<Idx>& get() const
  { return std::get<Idx>(values_); }

public:
  friend void swap(record& l, record& r) noexcept
  {
    using std::swap;
    swap(l.values_, r.values_);
  }

  template<std::size_t Idx>
  friend nth_value_type<Idx>& get(record& self)
  { return self.template get<Idx>(); }

  template<std::size_t Idx>
  friend const nth_value_type<Idx>& get(const record& self)
  { return self.template get<Idx>(); }

private:
  std::tuple<typename Columns::value_type...> values_;
};

template<typename... Columns>
constexpr inline record<Columns...> make_record(typename Columns::value_type... value)
{
  return { value... };
}

namespace detail
{

template<typename T, typename... Ts>
using index_of_t = std::integral_constant<int, (meta::size<meta::list<Ts...>>::value - meta::size<meta::find<meta::list<Ts...>, T>>::value)>;

template<typename Index, typename Record>
inline auto get(const Record& rec)
-> decltype(rec.template get<Index::value>())
{
  return rec.template get<Index::value>();
}

template<typename Index, typename Value, typename Record>
inline void set(Record& rec, const Value& x)
{
  rec.template get<Index::value>() = x;
}

} // namespace detail

template<
  typename... Columns,
  typename Column,
  typename = mpl::enable_if_t<is_column<Column>>
>
inline auto get(const record<Columns...>& r, const Column& col)
-> decltype(detail::get<detail::index_of_t<Column, Columns...> >(r))
{
  return detail::get<detail::index_of_t<Column, Columns...> >(r);
}

template<
  typename... Columns,
  typename... Column,
  typename = mpl::enable_if_t<meta::bool_<(sizeof...(Column) > 1)>>
>
inline auto get(const record<Columns...>& r, const Column&... col)
-> decltype(std::tie(get(r, col)...))
{
  return std::tie(get(r, col)...);
}

template<
  typename... Columns,
  typename Column,
  typename Value = typename Column::value_type,
  typename = mpl::enable_if_t<is_column<Column>>
>
inline void set(record<Columns...>& r, const Column& col, const Value& x)
{
  return detail::set<detail::index_of_t<Column, Columns...> >(r, x);
}

}

#endif
