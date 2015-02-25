/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef COLUMN_HPP_
#define COLUMN_HPP_

#include "field.hpp"
#include "primary_key.hpp"
#include "stringutil.hpp"
#include "table.hpp"

namespace fp
{

template<typename T>
using DescriptorOf = typename T::descriptor_type;

template<typename T>
using FieldOf = typename T::field_type;

template<typename /* Descriptor */, const char* /* Name */, typename /* Field */>
struct column;

template<typename>
struct is_column
: meta::bool_<false>
{ };

template<typename Descriptor, const char* Name, typename Field>
struct is_column<column<Descriptor, Name, Field> >
: is_field<Field>
{ };

namespace detail
{

template<typename Column, typename Descriptor>
constexpr static bool is_primary_key_of(std::true_type /* HasPrimaryKey */) noexcept
{ return Descriptor::primary_keys::template contains<Column>::value; }

template<typename Column, typename Descriptor>
constexpr static bool is_primary_key_of(std::false_type /* HasPrimaryKey */) noexcept
{ return false; }

template<typename Column, typename Descriptor>
constexpr static bool is_unique_key_of(std::true_type /* HasUniqueKeys */) noexcept
{ return Descriptor::unique_keys::template contains<Column>::value; }

template<typename Column, typename Descriptor>
constexpr static bool is_unique_key_of(std::false_type /* HasUniqueKeys */) noexcept
{ return false; }

template<typename Column, typename Descriptor>
constexpr static bool is_index_key_of(std::true_type /* HasIndexKeys */) noexcept
{ return Descriptor::index_keys::template contains<Column>::value; }

template<typename Column, typename Descriptor>
constexpr static bool is_index_key_of(std::false_type /* HasIndexKeys */) noexcept
{ return false; }

}

template<typename Descriptor, const char* Name, typename Field>
struct column
{
public:
  using this_type = column;
  using descriptor_type = Descriptor;
  using field_type = Field;
  using value_type = typename field_traits<Field>::value_type;

public:
  constexpr static descriptor_type descriptor()
  { return Descriptor { }; }

  constexpr static const char* name() noexcept
  { return Name; }

  constexpr static bool is_primary_key() noexcept
  { return detail::is_primary_key_of<this_type, Descriptor>(HasPrimaryKeys<Descriptor>{}); }

  constexpr static bool is_unique_key() noexcept
  { return detail::is_unique_key_of<this_type, Descriptor>(HasUniqueKeys<Descriptor>{}); }

  constexpr static bool is_index_key() noexcept
  { return detail::is_index_key_of<this_type, Descriptor>(HasIndexKeys<Descriptor>{}); }

public:
  template<typename Formatter>
  friend std::string to_string(const column& self, Formatter& formatter)
  {
    return stringutils::concatenate(formatter.to_string(self.descriptor()), ".", self.name());
  }
};

template<typename LColumn, typename RColumn, typename = typename mpl::enable_if<mpl::all_<is_column<LColumn>, is_column<RColumn> > >::type>
constexpr inline bool operator==(const LColumn& l,
                                 const RColumn& r)
{ return std::is_same<LColumn, RColumn>{}; }

template<typename LColumn, typename RColumn, typename = typename mpl::enable_if<mpl::all_<is_column<LColumn>, is_column<RColumn> > >::type>
constexpr inline bool operator!=(const LColumn& l,
                                 const RColumn& r)
{ return !(l == r); }

}

#endif
