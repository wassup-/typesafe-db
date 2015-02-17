/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _IS_CONTAINED_VALUE_IMPL_HPP
#define _IS_CONTAINED_VALUE_IMPL_HPP

#include "../type_traits.hpp"

namespace fp
{

namespace impl
{

template<typename T, T, T...>
struct is_contained_value_impl;

template<typename T, T I, T H, T... R>
struct is_contained_value_impl<T, I, H, R...> : is_contained_value_impl<T, I, R...> { };

template<typename T, T I, T... R>
struct is_contained_value_impl<T, I, I, R...> : mpl::true_ { };

template<typename T, T I, T H>
struct is_contained_value_impl<T, I, H> : mpl::false_ { };

template<typename T, T I>
struct is_contained_value_impl<T, I, I> : mpl::true_ { };

}

}

#endif
