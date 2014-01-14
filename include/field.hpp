/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _FIELD_HPP
#define _FIELD_HPP

#include "stringutil.hpp"       // for stringutils::concatenate
#include "table.hpp"            // for fp::table
#include "type_traits.hpp"      // for fp::Bool

#include <string>               // for std::string, std::to_string

namespace fp {
    
    template<typename /* Type */>
    struct field;

    template<typename>
    struct is_field : Bool<false> { };

    template<typename T>
    struct is_field<const T> : is_field<T> { };

    template<typename Type>
    struct is_field<field<Type>> : Bool<true> { };
    
    template<typename>
    struct field_traits;

    template<typename Type>
    struct field_traits<field<Type> > {
        using value_type = typename std::decay<Type>::type;
    };

    template<typename Type>
    struct field {
        using this_type = field;
        using value_type = typename std::decay<Type>::type;
    };
}

#endif