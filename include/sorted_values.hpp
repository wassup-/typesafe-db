/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _SORTED_VALUES_HPP
#define _SORTED_VALUES_HPP

#include "type_traits.hpp"
#include "impl/sorted_values_impl.hpp"

namespace fp {
	
    template<typename T, T... Vs>
    struct sorted_values : impl::sorted_values_impl<integer_sequence<T>, integer_sequence<T, Vs...>, integer_sequence<T> > { };
}

#endif