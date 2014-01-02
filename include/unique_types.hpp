/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _UNIQUE_TYPES_HPP
#define _UNIQUE_TYPES_HPP

#include "is_contained_type.hpp"
 #include "type_traits.hpp"

namespace fp {

    template<typename...>
    struct type_sequence;
    
    template<typename...>
    struct unique_types;

    namespace impl {
        
        template<typename, typename>
        struct unique_types_impl;
        
        template<bool, typename, typename>
        struct unique_types_helper;

        template<typename... TLeft, typename H, typename... T>
        struct unique_types_impl<type_sequence<TLeft...>, type_sequence<H, T...> >
        : identity<Invoke<unique_types_helper<is_contained_type<H, TLeft...>::value, type_sequence<TLeft...>, type_sequence<H, T...>>>> { };

        template<typename... TLeft>
        struct unique_types_impl<type_sequence<TLeft...>, type_sequence<> >
        : identity<type_sequence<TLeft...> > { };

        template<typename... TLeft, typename TRightHead, typename... TRightTail>
        struct unique_types_helper<false, type_sequence<TLeft...>, type_sequence<TRightHead, TRightTail...>>
        : identity<Invoke<unique_types_impl<type_sequence<TLeft..., TRightHead>, type_sequence<TRightTail...>>>> { };

        template<typename... TLeft, typename TRightHead, typename... TRightTail>
        struct unique_types_helper<true, type_sequence<TLeft...>, type_sequence<TRightHead, TRightTail...>>
        : identity<Invoke<unique_types_impl<type_sequence<TLeft...>, type_sequence<TRightTail...>>>> { };
    }

    template<typename H, typename... T>
    struct unique_types<H, T...> : impl::unique_types_impl<type_sequence<H>, type_sequence<T...>> { };
}

#endif