/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _SMALLEST_VALUE_HPP
#define _SMALLEST_VALUE_HPP

#include "impl/smallest_value_impl.hpp"

#include <cstddef>              // for int

namespace fp {
    template<int...> struct smallest_value;

    template<int H, int... T> struct smallest_value<H, T...> : impl::smallest_value_impl<H, T...>{
    };
}

#endif