/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _TABLE_HPP
#define _TABLE_HPP

#include "type_traits.hpp"

#include <string>

namespace fp {

    template<typename /* Descriptor */, const char* /* Name */>
    struct table;

    template<typename>
    struct is_table : Bool<false> { };
    
    template<typename Descriptor, const char* Name>
    struct is_table<table<Descriptor, Name>> : Bool<true> { };

    template<typename Descriptor, const char* Name>
    struct table {
    public:
        using this_type = table;
        using descriptor_type = Descriptor;
    public:
        constexpr const char* name() const noexcept {
            return Name;
        }
    public:
        friend std::string to_string(const table& t) {
            return t.name();
        }
    };

    namespace detail {

        template<typename Descriptor>
        struct has_primary_key_impl {

            struct yes {  char _; };
            struct no { yes _[2]; };

            template<typename T> static yes test(decltype(&Descriptor::primary_key));
            template<typename T> static no test(...);

            constexpr static bool value = (sizeof(yes) == (sizeof(test<Descriptor>(0))));
        };
    }

    template<typename Table>
    struct has_primary_key : Bool<detail::has_primary_key_impl<typename Table::descriptor_type>::value> { };

    template<typename T>
    using HasPrimaryKey = has_primary_key<T>;
}

#endif