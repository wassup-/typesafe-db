/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _LEXICAL_CAST_IMPL_HPP
#define _LEXICAL_CAST_IMPL_HPP

#include <boost/lexical_cast.hpp>

namespace fp
{

namespace impl
{

template<typename In, typename Out>
struct lexical_cast_impl
{
  static Out cast(const In& v)
  {
    return boost::lexical_cast<Out>(v);
  }
};

} // namespace impl

} // namespace fp

#endif
