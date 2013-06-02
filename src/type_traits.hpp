/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef TYPE_TRAITS_HPP_
#define TYPE_TRAITS_HPP_

#include <type_traits>

namespace fp {
    
    namespace impl {
        template<typename...> struct first_type_of;
        template<typename...> struct last_type_of;
        template<int, typename...> struct nth_type_of;
        
        template<typename H, typename... T>
        struct first_type_of<H, T...> { using type = H; };

        template<typename H, typename... T>
        struct last_type_of<H, T...> : last_type_of<T...> { };
        template<typename T>
        struct last_type_of<T> { using type = T; };
        
        template<int I, typename H, typename... T>
        struct nth_type_of<I, H, T...> : nth_type_of<(I - 1), T...> { };
        template<typename H, typename... T>
        struct nth_type_of<0, H, T...> { using type = H; };
    }
    
    template<typename T>
    using Invoke = typename T::type;
    
    template<typename T>
    struct identity {
        using type = T;
    };
    
    template<bool B, typename...>
    struct dependent_bool_type : std::integral_constant<bool, B> { };
    
    template<bool B, typename... T>
    using Bool = Invoke<dependent_bool_type<B, T...>>;
    
    template<typename T, T V>
    using Const = std::integral_constant<T, V>;
    
    template<int I>
    using Int = Const<decltype(I), I>;
    
    template<typename T>
    using Identity = Invoke<identity<T>>;
    
    template<typename T>
    using Alias = T;
    
    template<typename T>
    using NotDeducible = Identity<T>;

    template<typename T>
    using RemoveCv = Invoke<std::remove_cv<T>>;

    template<typename T>
    using RemoveReference = Invoke<std::remove_reference<T>>;

    template<typename T>
    using Unqualified = RemoveCv<RemoveReference<T>>;
    
    template<typename If, typename Then, typename Else>
    using Conditional = Invoke<std::conditional<If::value, Then, Else>>;
    
    template<typename T>
    using Not = Bool<!T::value>;
    
    template<typename... T> 
    struct Any : Bool<false> { };
    template<typename H, typename... T> 
    struct Any<H, T...> : Conditional<H, Bool<true>, Any<T...>> { };
    
    template<typename... T>
    struct All : Bool<true> { };
    template<typename H, typename... T>
    struct All<H, T...> : Conditional<H, All<T...>, Bool<false>> { };
    
    template<typename... T>
    using FirstTypeOf = Invoke<impl::first_type_of<T...>>;
    
    template<typename... T>
    using LastTypeOf = Invoke<impl::last_type_of<T...>>;
    
    template<int I, typename... T>
    using NthTypeOf = Invoke<impl::nth_type_of<I, T...>>;
    
    template<typename> struct result_of;
    template<int> struct indexed;
    template<typename, template<typename...> class> struct is_specialization_of;
    
    template<typename TType, template<typename...> class TTemplate>
    struct is_specialization_of : Bool<true> { };
    template<template<typename...> class TTemplate, typename... TArgs>
    struct is_specialization_of<TTemplate<TArgs...>, TTemplate> : Bool<false> { };
    
    template<typename Head, typename... Tail>
    struct min : Head { };
    template<typename T, typename U, typename... Tail>
    struct min<T, U, Tail...> : min<Conditional<Bool<(T::value < U::value)>, T, U>, Tail...> { };
    
    template<typename Head, typename... Tail>
    struct max : Head { };
    template<typename T, typename U, typename... Tail>
    struct max<T, U, Tail...> : max<Conditional<Bool<(T::value > U::value)>, T, U>, Tail...> { };
    
    template<typename... T>
    struct count : Int<0> { };
    template<typename Head, typename... Tail>
    struct count<Head, Tail...> : Int<(!!Head::value) + count<Tail...>::value> { };
    
    namespace detail {
        enum class enabler { _ };
    }
    
    constexpr auto _ = detail::enabler::_;
    
    template<typename... TCond>
    using EnableIf = Invoke<std::enable_if<All<TCond...>::value, decltype(_)>>;
    
    template<typename... TCond>
    using DisableIf = Invoke<std::enable_if<Not<All<TCond...>>::value, decltype(_)>>;
    
    template<typename... T>
    struct is_same : Bool<false> { };
    template<typename T, typename U, typename... Tail>
    struct is_same<T, U, Tail...> : Conditional<std::is_same<T, U>, is_same<U, Tail...>, Bool<false>> { };
    
    template<int Idx>
    struct indexed {
        using value_type = int;
        constexpr static int index = Idx;

        constexpr operator value_type() const {
            return index;
        }
    };
}

#endif