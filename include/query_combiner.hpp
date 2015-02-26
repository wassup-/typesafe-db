/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _QUERY_COMBINER_HPP
#define _QUERY_COMBINER_HPP

#include "impl/query_combiner_impl.hpp"

namespace fp
{

template<
  template<typename...> class Query,
  typename... LColumns,
  typename... RColumns,
  typename = mpl::enable_if_t<mpl::all_<is_column<LColumns>..., is_column<RColumns>...> >
>
constexpr inline typename impl::query_combiner_impl<Query, LColumns..., RColumns...>::normal
combine(const Query<LColumns...>&, const Query<RColumns...>&)
{
  return { };
}

template<
  template<typename...> class Query,
  typename... LColumns,
  typename... RColumns,
  typename = mpl::enable_if_t<mpl::all_<is_column<LColumns>..., is_column<RColumns>...> >
>
constexpr inline typename impl::query_combiner_impl<Query, LColumns..., RColumns...>::unique
combine_unique(const Query<LColumns...>&, const Query<RColumns...>&)
{
  return { };
}

} // namespace fp

#endif
