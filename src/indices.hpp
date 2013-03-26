/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _INDICES_HPP
#define _INDICES_HPP

#include <cstddef>              // for int

namespace fp {

    template <int...> struct indices {
    };

    template <int N, int... Is> struct build_indices : build_indices<N - 1, N - 1, Is...> {
    };

    template <int... Is> struct build_indices < 0, Is...> : indices<Is...> {
    };
}

#endif