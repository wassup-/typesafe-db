/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _TABLE_HPP
#define _TABLE_HPP

#include "type_traits.hpp"

namespace fp {
    
    template<typename...>
    struct record;

    template<typename...>
    struct table;

    template<typename TDescriptor, int... Indices, typename... TTypes>
    struct table<field<TDescriptor, Indices, TTypes>...> {
        
        using types = type_sequence<TTypes...>;

        struct record {
            using type = fp::record<field<TDescriptor, Indices, TTypes>...>;
        };

        friend std::string to_string(const table&) {
            return TDescriptor::table::name;
        }
    };

    namespace detail {

        template<typename TTable>
        struct has_primary_key_impl {

            struct yes {  char _; };
            struct no { yes _[2]; };

            template<typename T> static yes test(typename T::primary_key *);
            template<typename T> static no test(...);

            CONSTEXPR static bool value = (sizeof(yes) == (sizeof(test<TTable>(0))));
        };
    }

    template<typename TTable>
    struct has_primary_key : Bool<detail::has_primary_key_impl<TTable>::value> { };
    
    template<typename T>
    using HasPrimaryKey = has_primary_key<T>;
}

#endif