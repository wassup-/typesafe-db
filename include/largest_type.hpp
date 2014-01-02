/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _LARGEST_TYPE_H
#define _LARGEST_TYPE_H

#include "impl/largest_type_impl.hpp"

#include "type_sequence.hpp"

namespace fp {

    template<typename... Ts>
    struct largest_type : impl::largest_type_impl<Ts...> { };
}

#endif