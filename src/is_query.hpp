/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _IS_QUERY_HPP
#define _IS_QUERY_HPP

#include "type_traits.hpp"

namespace fp {

    template<typename>
    struct is_query          : Bool<false> { };
    
    template<typename>
    struct is_where_query    : Bool<false> { };
    
    template<typename>
    struct is_select_query   : Bool<false> { };
    
    template<typename>
    struct is_update_query   : Bool<false> { };
    
    template<typename>
    struct is_insert_query   : Bool<false> { };
    
    template<typename>
    struct is_limit_query    : Bool<false> { };
    
    template<typename>
    struct is_ordered_query  : Bool<false> { };
}

#endif