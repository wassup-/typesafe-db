/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _QUERY_COMBINER_IMPL_HPP
#define _QUERY_COMBINER_IMPL_HPP

#include "../unique_types.hpp"

namespace fp
{

template<typename...>
struct select_query;

namespace impl
{

template<typename...>
struct query_combiner_impl;

template<typename>
struct make_select_query;

template<typename... TFields>
struct make_select_query<mpl::type_sequence<TFields...> > : mpl::identity<select_query<TFields...>> { };

template<typename... TFields>
struct query_combiner_impl
{
  struct normal : mpl::identity<select_query<TFields...>> { };
  struct unique : mpl::identity<Invoke<make_select_query<Invoke<unique_types<TFields...>>>>> { };
};

}

}

#endif
