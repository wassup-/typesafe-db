/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _TABLE_HPP
#define _TABLE_HPP

#include "type_traits.hpp"

#include <string>

namespace fp
{

template<typename /* Descriptor */, const char* /* Name */>
struct table;

template<typename>
struct is_table : mpl::false_ { };

template<typename Descriptor, const char* Name>
struct is_table<table<Descriptor, Name>> : mpl::true_ { };

template<typename Descriptor, const char* Name>
struct table
{
public:
  using this_type = table;
  using descriptor_type = Descriptor;

public:
  constexpr const char* name() const noexcept
  { return Name; }

public:
  friend std::string to_string(const table& t)
  { return t.name(); }
};

namespace detail
{

template<typename Descriptor>
struct has_primary_key_impl
{
  template<typename T>
  static std::true_type test(typename T::primary_key*);

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

template<typename Table>
struct has_primary_key : detail::has_primary_key_impl<typename Table::descriptor_type>::type { };
template<typename Table>
struct has_primary_key<const Table> : has_primary_key<Table> { };

template<typename T>
using HasPrimaryKey = typename detail::has_primary_key_impl<T>::type;

template<typename T>
using HasUniqueKeys = typename detail::has_unique_keys_impl<T>::type;

template<typename T>
using HasIndexKeys = typename detail::has_index_keys_impl<T>::type;

} // namespace fp

#endif
