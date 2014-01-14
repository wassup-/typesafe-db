/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _IS_QUERY_HPP
#define _IS_QUERY_HPP

#include "type_traits.hpp"

namespace fp {

    template<typename>
    struct is_query          : Bool<false> { };
    template<typename T>
    struct is_query<const T> : is_query<T> { };
    
    template<typename>
    struct is_where_query    : Bool<false> { };
    template<typename T>
    struct is_where_query<const T> : is_where_query<T> { };
    
    template<typename>
    struct is_select_query   : Bool<false> { };
    template<typename T>
    struct is_select_query<const T> : is_select_query<T> { };
    
    template<typename>
    struct is_update_query   : Bool<false> { };
    template<typename T>
    struct is_update_query<const T> : is_update_query<T> { };
    
    template<typename>
    struct is_insert_query   : Bool<false> { };
    template<typename T>
    struct is_insert_query<const T> : is_insert_query<T> { };
    
    template<typename>
    struct is_limit_query    : Bool<false> { };
    template<typename T>
    struct is_limit_query<const T> : is_limit_query<T> { };
    
    template<typename>
    struct is_ordered_query  : Bool<false> { };
    template<typename T>
    struct is_ordered_query<const T> : is_ordered_query<T> { };
}

#endif