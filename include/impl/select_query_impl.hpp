/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _SELECT_QUERY_IMPL_HPP
#define _SELECT_QUERY_IMPL_HPP

#include "../config.hpp"
#include "../stringutil.hpp"

#include <string>       // for std::string, std::to_string

namespace fp
{

namespace impl
{

template<typename... /* Descriptors */>
struct table_names;

template<typename... TDescriptors>
struct table_names
{
  constexpr static std::size_t size = sizeof...(TDescriptors);
  constexpr static const char* const names[size] = { TDescriptors::this_type::name()... };
};

template<typename... TDescriptors>
constexpr const char* const table_names<TDescriptors...>::names[table_names<TDescriptors...>::size];

template<typename... TColumns>
struct select_query_impl
{
  template<typename Formatter>
  static std::string build_select_query(const TColumns&... f, Formatter& formatter)
  {
    using list = meta::list<TColumns...>;
    using transformed = meta::transform<list, meta::quote<DescriptorOf>>;
    using unique = meta::unique<transformed>;
    using tables = meta::apply_list<meta::quote<table_names>, unique>;

    return stringutils::concatenate(
      "SELECT ",
      stringutils::implode(", ", formatter.to_string(f)...),
      " FROM ",
      stringutils::implode(", ", tables::names)
    );
  }
};

}

}

#endif
