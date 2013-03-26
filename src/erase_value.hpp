/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _ERASE_VALUE_HPP
#define _ERASE_VALUE_HPP

#include "impl/erase_value_impl.hpp"

#include <cstddef>              // for int

namespace fp {
    template<int...> struct int_seq;
    template<int, int...> struct erase_value;

    template<int I, int... T> struct erase_value : impl::erase_value_impl<I, int_seq<>, int_seq < T...> > {
    };
}

#endif