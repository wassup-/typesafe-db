/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _TABLE_HPP
#define _TABLE_HPP

#include "int_sequence.hpp"
#include "type_sequence.hpp"

namespace fp {
    template<typename...>
    struct record;
    
    template<typename...>
    struct table;

    template<typename TDescriptor, int... Indices, typename... TTypes>
    struct table<field<TDescriptor, Indices, TTypes>...> {
        typedef type_seq < TTypes...> types;

        struct record {
            using type = fp::record<field<TDescriptor, Indices, TTypes>...>;
        };
        
        friend std::string to_string(table const &) {
            return TDescriptor::table::name;
        }
    };
}

#endif