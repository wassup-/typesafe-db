/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _TABLE_HPP
#define _TABLE_HPP

#include "type_traits.hpp"

#include <string>

namespace fp
{

template<typename...>
struct record;

template<typename /* Descriptor */>
struct table;

template<typename>
struct is_table
: meta::bool_<false>
{ };

template<typename Descriptor>
struct is_table<table<Descriptor> >
: meta::bool_<true>
{ };

namespace detail
{

template<typename Descriptor>
struct has_primary_keys_impl
{
  template<typename T>
  static std::true_type test(typename T::primary_keys*);

  template<typename T>
  static std::false_type test(...);

  using type = decltype(test<Descriptor>(nullptr));
};

template<typename Descriptor>
struct has_unique_keys_impl
{
  template<typename T>
  static std::true_type test(typename T::unique_keys*);

  template<typename T>
  static std::false_type test(...);

  using type = decltype(test<Descriptor>(nullptr));
};

template<typename Descriptor>
struct has_index_keys_impl
{
  template<typename T>
  static std::true_type test(typename T::index_keys*);

  template<typename T>
  static std::false_type test(...);

  using type = decltype(test<Descriptor>(nullptr));
};

} // namespace detail

template<typename T>
using HasPrimaryKeys = meta::eval<detail::has_primary_keys_impl<T> >;

template<typename T>
using HasUniqueKeys = meta::eval<detail::has_unique_keys_impl<T> >;

template<typename T>
using HasIndexKeys = meta::eval<detail::has_index_keys_impl<T> >;

namespace detail
{

template<typename, typename>
struct table_helper;

template<typename Descriptor, typename... Columns>
struct table_helper<Descriptor, record<Columns...>>
{
  using record_type = record<Columns...>;

  template<typename Key, typename Engine>
  static record_type by_primary(Key k, Engine& engine)
  {
    auto sq = select(Columns{}...);
    auto wq = where(k);
    return engine.query(sq + wq, Engine::single_result);
  }

  template<typename Key, typename Engine>
  static record_type by_unique(Key k, Engine& engine)
  {
    auto sq = select(Columns{}...);
    auto wq = where(k);
    return engine.query(sq + wq, Engine::single_result);
  }

  template<typename Key, typename Engine>
  static record_type by_index(Key k, Engine& engine)
  {
    auto sq = select(Columns{}...);
    auto wq = where(k);
    auto res = engine.query(sq + wq);
    return res[0];
  }
};

} // namespace detail

template<typename Descriptor>
struct table
{
public:
  using this_type = table;
  using descriptor_type = Descriptor;

public:
  constexpr static const char* name() noexcept
  { return Descriptor::_name(); }

public:
  template<typename Key, typename Engine, typename U = Descriptor, typename = mpl::enable_if<HasPrimaryKeys<U> > >
  static typename U::record_type by_primary(Key x, Engine& engine)
  {
    return detail::table_helper<U, typename U::record_type>::by_primary(x, engine);
  }

  template<typename Key, typename Engine, typename U = Descriptor, typename = mpl::enable_if<HasUniqueKeys<U> > >
  static typename U::record_type by_unique(Key x, Engine& engine)
  {
    return detail::table_helper<U, typename U::record_type>::by_unique(x, engine);
  }

  template<typename Key, typename Engine, typename U = Descriptor, typename = mpl::enable_if<HasIndexKeys<U> > >
  static typename U::record_type by_index(Key x, Engine& engine)
  {
    return detail::table_helper<U, typename U::record_type>::by_index(x, engine);
  }

public:
  template<typename Formatter>
  friend std::string to_string(const Descriptor& self, Formatter& formatter)
  { return name(); }
};

} // namespace fp

#endif
