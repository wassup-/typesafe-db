/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef TYPE_TRAITS_HPP_
#define TYPE_TRAITS_HPP_

#include <type_traits>

namespace fp {

    template<typename T>
    using Invoke = typename T::type;

    template<typename T>
    struct identity { using type = T; };

    template<typename T>
    using Identity = Invoke<identity<T>>;

    namespace detail {

        template<std::size_t, typename, typename...>
        struct type_index;
        template<std::size_t I, typename T>
        struct type_index<I, T>;

        template<std::size_t I, typename T, typename H, typename... R>
        struct type_index<I, T, H, R...> : type_index<(I + 1), T, R...> { };
        template<std::size_t I, typename T, typename... R>
        struct type_index<I, T, T, R...> : std::integral_constant<std::size_t, I> { };

        template<std::size_t, typename T, T, T...>
        struct value_index;
        template<std::size_t I, typename T, T V>
        struct value_index<I, T, V>;

        template<std::size_t I, typename T, T V, T H, T... R>
        struct value_index<I, T, V, H, R...> : value_index<(I + 1), T, V, R...> { };
        template<std::size_t I, typename T, T V, T... R>
        struct value_index<I, T, V, V, R...> : std::integral_constant<std::size_t, I> { };
    }

    template<typename... Ts>
    struct type_sequence {
        
        template<template<typename...> class C>
        struct as : identity<C<Ts...>> { };

        template<typename T>
        struct index_of : detail::type_index<0, T, Ts...> { };
    };

    template<typename T, T... Vs>
    struct integer_sequence {
        
        template<template<T...> class C>
        struct as : identity<C<Vs...>> { };

        template<T V>
        struct index_of : detail::value_index<0, T, V, Vs...> { };
    };

    template<std::size_t... Idx>
    using index_sequence = integer_sequence<std::size_t, Idx...>;

    template<typename T, typename... Ts>
    using IndexOfType = typename type_sequence<Ts...>::template index_of<T>;
    
    template<typename T, T V, T... Vs>
    using IndexOfValue = typename integer_sequence<T, Vs...>::template index_of<V>;

    namespace detail {

        template<typename, typename...>
        struct type_indices;
        template<typename T, T, T...>
        struct value_indices;

        template<typename T /* Integer type */, typename /* Known indices */, std::size_t, T, T...>
        struct value_indices_impl;

        template<typename T, std::size_t... Known, std::size_t I, T V, T H, T... R>
        struct value_indices_impl<T, index_sequence<Known...>, I, V, H, R...>
        : value_indices_impl<T, index_sequence<Known...>, (I + 1), V, R...> { };

        template<typename T, std::size_t... Known, std::size_t I, T V, T... R>
        struct value_indices_impl<T, index_sequence<Known...>, I, V, V, R...>
        : value_indices_impl<T, index_sequence<Known..., I>, (I + 1), V, R...> { };

        template<typename T, std::size_t... Known, std::size_t I, T V>
        struct value_indices_impl<T, index_sequence<Known...>, I, V>
        : identity<index_sequence<Known...>> { };

        template<typename T, typename... Ts>
        struct type_indices : value_indices<std::size_t, 1, std::is_same<T, Ts>::value...> { };

        template<typename T, T V, T... Vs>
        struct value_indices : value_indices_impl<T, index_sequence<>, 0, V, Vs...> { };
    }

    template<typename T, typename... Ts>
    using IndicesOfType = Invoke<detail::type_indices<T, Ts...>>;

    template<typename T, T V, T... Vs>
    using IndicesOfValue = Invoke<detail::value_indices<T, V, Vs...>>;
    
    template<bool B, typename...>
    struct dependent_bool_type : std::integral_constant<bool, B> { };
    
    template<bool B, typename... T>
    using Bool = Invoke<dependent_bool_type<B, T...>>;
    
    template<typename T, T V>
    using Const = std::integral_constant<T, V>;
    
    template<int I>
    using Int = Const<decltype(I), I>;

    template<std::size_t I>
    using Index = Const<std::size_t, I>;
    
    template<typename T>
    using Alias = T;
    
    template<typename T>
    using NotDeducible = Identity<T>;

    template<typename If, typename Then, typename Else>
    using Conditional = Invoke<std::conditional<If::value, Then, Else>>;
    
    template<typename T>
    using RemoveConst = Invoke<std::remove_const<T>>;
    
    template<typename T>
    using RemoveVolatitle = Invoke<std::remove_volatile<T>>;

    template<typename T>
    using RemoveCv = Invoke<std::remove_cv<T>>;
    
    template<typename T>
    using RemoveReference = Invoke<std::remove_reference<T>>;
    
    template<typename T>
    using AddConst = Invoke<std::add_const<T>>;
    
    template<typename T>
    using AddVolatile = Invoke<std::add_volatile<T>>;
    
    template<typename T>
    using AddCv = Invoke<std::add_cv<T>>;
    
    template <typename T>
    using AddLvalueReference = Invoke<std::add_lvalue_reference<T>>;

    template <typename T>
    using AddRvalueReference = Invoke<std::add_rvalue_reference<T>>;

    template<typename T>
    using Unqualified = RemoveCv<RemoveReference<T>>;
    
    template<typename T>
    using Decay = Invoke<std::decay<T>>;
    
    template<typename... T>
    using CommonType = Invoke<std::common_type<T...>>;

    /*template<typename T>
    using UnderlyingType = Invoke<std::underlying_type<T>>;*/

    template <typename T>
    using MakeSigned = Invoke<std::make_signed<T>>;

    template<typename T>
    using MakeUnsigned = Invoke<std::make_unsigned<T>>;

    template<typename T>
    using RemoveExtent = Invoke<std::remove_extent<T>>;

    template<typename T>
    using RemoveAllExtents = Invoke<std::remove_all_extents<T>>;

    template<typename T>
    using RemovePointer = Invoke<std::remove_pointer<T>>;

    template<typename T>
    using AddPointer = Invoke<std::add_pointer<T>>;
    
    template<typename Source, typename Destination>
    using WithConstOf = Conditional<std::is_const<Source>, AddConst<Destination>, Destination>;

    template<typename Source, typename Destination>
    using WithVolatileOf = Conditional<std::is_volatile<Source>, AddVolatile<Destination>, Destination>;

    template<typename Source, typename Destination>
    using WithCvOf = WithConstOf<Source, WithVolatileOf<Source, Destination>>;
    
    template<typename Source, typename Destination>
    using WithValueCategoryOf =
        Conditional<std::is_lvalue_reference<Source>,
            AddLvalueReference<Destination>,
            Conditional<std::is_rvalue_reference<Source>,
                AddRvalueReference<Destination>,
                Destination
            >
        >;
    
    template<typename Source, typename Destination>
    using WithQualificationsOf = WithValueCategoryOf<Source, WithCvOf<RemoveReference<Source>, Destination>>;

    template<typename T, typename U>
    using is_related = std::is_same<Unqualified<T>, Unqualified<U>>;
    
    template<typename T>
    using IsUnqualified = std::is_same<T, Unqualified<T>>;
    
    template<typename T>
    using Not = Bool<!T::value>;
    
    namespace impl {
        
        template<typename... T>
        struct any : Bool<false> { };
        template<typename H, typename... T>
        struct any<H, T...> : Conditional<H, Bool<true>, any<T...>> { };
        
        template<typename... T>
        struct all : Bool<true> { };
        template<typename H, typename... T>
        struct all<H, T...> : Conditional<H, all<T...>, Bool<false>> { };
    }
    
    template<typename... T> 
    struct Any : impl::any<T...> { };
    
    template<typename... T>
    struct All : impl::all<T...> { };
    
    namespace impl {
        
        template<typename...> struct first_type_of;
        template<typename...> struct last_type_of;
        template<std::size_t, typename...> struct nth_type_of;
        
        template<typename H, typename... T>
        struct first_type_of<H, T...> : identity<H> { };

        template<typename H, typename... T>
        struct last_type_of<H, T...> : last_type_of<T...> { };
        template<typename T>
        struct last_type_of<T> : identity<T> { };
        
        template<std::size_t I, typename H, typename... T>
        struct nth_type_of<I, H, T...> : nth_type_of<(I - 1), T...> { };
        template<typename H, typename... T>
        struct nth_type_of<0, H, T...> : identity<H> { };
    }
    
    template<typename... T>
    using FirstTypeOf = Invoke<impl::first_type_of<T...>>;
    
    template<typename... T>
    using LastTypeOf = Invoke<impl::last_type_of<T...>>;
    
    template<std::size_t I, typename... T>
    using NthTypeOf = Invoke<impl::nth_type_of<I, T...>>;
    
    namespace impl {
        
        template<typename T, T...> struct first_value_of;
        template<typename T, T...> struct last_value_of;
        template<std::size_t, typename T, T...> struct nth_value_of;
        
        template<typename T, T H, T... R>
        struct first_value_of<T, H, R...> : Const<T, H> { };

        template<typename T, T H, T... R>
        struct last_value_of<T, H, R...> : last_value_of<T, R...> { };
        template<typename T, T V>
        struct last_value_of<T, V> : Const<T, V> { };
        
        template<std::size_t I, typename T, T H, T... R>
        struct nth_value_of<I, T, H, R...> : nth_value_of<(I - 1), T, R...> { };
        template<typename T, T H, T... R>
        struct nth_value_of<0, T, H, R...> : Const<T, H> { };
    }
    
    template<typename T, T... V>
    using FirstValueOf = Invoke<impl::first_value_of<T, V...>>;
    
    template<typename T, T... V>
    using LastValueOf = Invoke<impl::last_value_of<T, V...>>;
    
    template<std::size_t I, typename T, T... V>
    using NthValueOf = Invoke<impl::nth_value_of<I, T, V...>>;
    
    namespace impl {
        
        template<int, typename...>
        struct skip_n_types;
        
        template<int N, typename H, typename... T>
        struct skip_n_types<N, H, T...> : skip_n_types<(N - 1), T...> { };
        
        template<typename... T>
        struct skip_n_types<0, T...> : identity<type_sequence<T...>> { };
        
        template<typename T, int N, T...>
        struct skip_n_values;
        
        template<typename T, int N, T H, T... Tail>
        struct skip_n_values<T, N, H, Tail...> : skip_n_values<T, (N - 1), Tail...> { };
        
        template<typename T, int... Tail>
        struct skip_n_values<T, 0, Tail...> : identity<integer_sequence<T, Tail...>> { };
    }
    
    template<int N, typename... T>
    using SkipTypes = Invoke<impl::skip_n_types<N, T...>>;
    
    template<int N, int... T>
    using SkipValues = Invoke<impl::skip_n_values<int, N, T...>>;
    
    namespace impl {
        
        template<typename T>
        struct result_of : identity<Invoke<T>> { };
        
        template<typename TRet, typename... TArg>
        struct result_of<TRet(*)(TArg...) > : identity<TRet> { };

        template<typename TClass, typename TRet, typename... TArg>
        struct result_of<TRet(TClass::*)(TArg...)> : identity<TRet> { };

        template<typename Fn, typename... Arg>
        struct result_of<Fn(Arg...)> : identity<Invoke<std::result_of<Fn(Arg...)>>> { };
    }
    
    template<typename T>
    using ResultOf = Invoke<impl::result_of<T>>;
    
    template<typename, template<typename...> class>
    struct is_specialization_of;
    template<typename TType, template<typename...> class TTemplate>
    struct is_specialization_of : Bool<true> { };
    template<template<typename...> class TTemplate, typename... TArgs>
    struct is_specialization_of<TTemplate<TArgs...>, TTemplate> : Bool<false> { };
    
    namespace impl {
        
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
    }
    
    template<typename... T>
    struct min : impl::min<T...> { };
    
    template<typename... T>
    struct max : impl::max<T...> { };
    
    template<typename... T>
    struct count : impl::count<T...> { };
    
    namespace detail {
        enum class enabler { _ };
    }
    
    constexpr auto _ = detail::enabler::_;
    
    template<typename... TCond>
    using EnableIf = Invoke<std::enable_if<All<TCond...>::value, decltype(_)>>;
    
    template<typename... TCond>
    using DisableIf = Invoke<std::enable_if<Not<All<TCond...>>::value, decltype(_)>>;
    
    namespace impl {
        
        template<typename...>
        struct is_same : Bool<false> { };
        
        template<typename T, typename U, typename... Tail>
        struct is_same<T, U, Tail...> : Conditional<std::is_same<T, U>, is_same<U, Tail...>, Bool<false>> { };
    }
    
    template<typename... T>
    struct is_same : impl::is_same<T...> { };
}

#endif