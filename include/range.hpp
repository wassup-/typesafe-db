/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _RANGE_HPP
#define _RANGE_HPP

#include "impl/range_impl.hpp"

namespace fp {
	
    template<int, int>
    struct range_builder;

    template<int Min, int Max>
    struct range_builder : impl::range_builder_impl < (Min <= Max), Min, Max> {
    };

    template<int Min, int Max>
    CONSTEXPR typename range_builder<Min, Max>::type make_range() {
        return { };
    }
}

#endif