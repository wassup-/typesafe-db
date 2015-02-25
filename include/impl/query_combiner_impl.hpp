/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _QUERY_COMBINER_IMPL_HPP
#define _QUERY_COMBINER_IMPL_HPP

#include "../meta.hpp"

namespace fp
{

namespace impl
{

template<template<typename...> class TQuery, typename... TColumns>
struct query_combiner_impl
{
  using list = meta::list<TColumns...>;

  using normal = meta::apply_list<meta::quote<TQuery>, list>;
  using unique = meta::apply_list<meta::quote<TQuery>, meta::unique<list>>;
};

} // namespace impl

} // namespace fp

#endif
