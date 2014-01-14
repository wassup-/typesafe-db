/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _TYPE_EXTRACTOR_HPP
#define _TYPE_EXTRACTOR_HPP

#include "type_traits.hpp"

namespace fp {
    
    template<typename, typename>
    struct extract_types;

    template<typename T, T... I, typename... Ts>
    struct extract_types<integer_sequence<T, I...>, type_sequence<Ts...>>
    : identity<type_sequence<NthTypeOf<I, Ts...>...>> { };
}

#endif