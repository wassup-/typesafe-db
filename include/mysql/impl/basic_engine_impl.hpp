/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _MYSQL_ENGINE_IMPL_HPP
#define _MYSQL_ENGINE_IMPL_HPP

#include "../basic_row.hpp"
#include "../../forward.hpp"

#include <utility>      // for fix::forward

namespace fp { namespace mysql { namespace impl {

  template<typename /* Record */>
  struct make_record;

  template<int, typename>
  struct make_record_impl;

  template<int I, typename TRecord>
  struct make_record_impl
  {
    template<typename... TArg>
    constexpr static TRecord make(const mysql::basic_row& r, TArg&&... arg)
    {
      using value_type = typename TRecord::template nth_value_type<(I - 1)>;
      return make_record_impl<(I - 1), TRecord>::make(r, get<(I - 1), value_type>(r), fix::forward<TArg>(arg)...);
    }
  };

  template<typename TRecord>
  struct make_record_impl<0, TRecord>
  {
    template<typename... TArg>
    constexpr static TRecord make(const mysql::basic_row& r, TArg&&... arg)
    {
      return { fix::forward<TArg>(arg)... };
    }
  };

  template<typename TRecord>
  struct make_record
  {
    constexpr static TRecord make(const mysql::basic_row& r)
    {
      return make_record_impl<TRecord::size(), TRecord>::make(r);
    }
  };
} } }

#endif
