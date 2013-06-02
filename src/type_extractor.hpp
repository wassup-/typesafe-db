/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _TYPE_EXTRACTOR_HPP
#define _TYPE_EXTRACTOR_HPP

#include "type_traits.hpp"

namespace fp {
    template<int...>
    struct int_seq;
    
    template<typename...>
    struct type_seq;
    
    template<typename, typename>
    struct extract_types;

    template<int... I, typename... T>
    struct extract_types<int_seq<I...>, type_seq<T...> > {
        using type = type_seq<NthTypeOf<I, T...>>;
    };
}

#endif