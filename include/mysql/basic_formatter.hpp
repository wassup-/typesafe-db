/* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/.*/

#ifndef MYSQL_BASIC_FORMATTER_HPP
#define MYSQL_BASIC_FORMATTER_HPP

#include "../column.hpp"
#include "../type_traits.hpp"

#include <string>               // for std::string, std::to_string

namespace fp
{

namespace mysql
{

namespace detail
{

template<typename T, typename Formatter>
std::string to_string(const T& x, Formatter& formatter)
{
  return std::to_string(x);
}

template<typename Formatter>
std::string to_string(const std::string& x, Formatter& formatter)
{
  return x;
}

template<typename T, typename Formatter>
inline std::string to_string_impl(const T& x, Formatter& formatter)
{
  using detail::to_string;
  return to_string(x, formatter);
}

}

class basic_formatter
{
public:
  using this_type = basic_formatter;

public:
  template<typename T>
  auto to_string(const T& x)
  -> decltype(detail::to_string_impl(x, std::declval<this_type&>()))
  {
    return detail::to_string_impl(x, *this);
  }
};

} // namespace mysql

} // namespace fp

#endif
