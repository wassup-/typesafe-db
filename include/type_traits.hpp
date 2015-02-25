/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef TYPE_TRAITS_HPP_
#define TYPE_TRAITS_HPP_

#include "meta.hpp"
#include "mpl/mpl.hpp"

#include <type_traits>

namespace fp
{

template<typename T>
using Invoke = meta::eval<T>;

namespace detail
{

template<typename, typename...>
struct type_indices;
template<typename T, T, T...>
struct value_indices;

template<typename T /* Integer type */, typename /* Known indices */, std::size_t, T, T...>
struct value_indices_impl;

template<typename T, std::size_t... Known, std::size_t I, T V, T H, T... R>
struct value_indices_impl<T, mpl::indices_<Known...>, I, V, H, R...>
: value_indices_impl<T, mpl::indices_<Known...>, (I + 1), V, R...> { };

template<typename T, std::size_t... Known, std::size_t I, T V, T... R>
struct value_indices_impl<T, mpl::indices_<Known...>, I, V, V, R...>
: value_indices_impl<T, mpl::indices_<Known..., I>, (I + 1), V, R...> { };

template<typename T, std::size_t... Known, std::size_t I, T V>
struct value_indices_impl<T, mpl::indices_<Known...>, I, V>
: meta::id<mpl::indices_<Known...>> { };

template<typename T, typename... Ts>
struct type_indices : value_indices<std::size_t, 1, std::is_same<T, Ts>::value...> { };

template<typename T, T V, T... Vs>
struct value_indices : value_indices_impl<T, mpl::indices_<>, 0, V, Vs...> { };

} // namespace detail

template<typename T, typename... Ts>
using IndicesOfType = Invoke<detail::type_indices<T, Ts...>>;

template<typename T, T V, T... Vs>
using IndicesOfValue = Invoke<detail::value_indices<T, V, Vs...>>;

template<typename... T>
using FirstTypeOf = meta::front<meta::list<T...>>;

template<typename... T>
using LastTypeOf = meta::back<meta::list<T...>>;

template<std::size_t I, typename... T>
using NthTypeOf = meta::list_element_c<I, meta::list<T...>>;

template<typename T, T... V>
using FirstValueOf = FirstTypeOf<std::integral_constant<T, V>...>;

template<typename T, T... V>
using LastValueOf = LastTypeOf<std::integral_constant<T, V>...>;

template<std::size_t I, typename T, T... V>
using NthValueOf = NthTypeOf<I, std::integral_constant<T, V>...>;

template<int N, typename... T>
using SkipTypes = meta::drop_c<N, meta::list<T...>>;

template<int N, int... T>
using SkipValues = SkipTypes<N, std::integral_constant<int, T>...>;


template<typename T>
using Alias = T;

template<typename T>
using NotDeducible = meta::id<T>;

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
using WithConstOf = meta::if_<std::is_const<Source>, AddConst<Destination>, Destination>;

template<typename Source, typename Destination>
using WithVolatileOf = meta::if_<std::is_volatile<Source>, AddVolatile<Destination>, Destination>;

template<typename Source, typename Destination>
using WithCvOf = WithConstOf<Source, WithVolatileOf<Source, Destination>>;

template<typename Source, typename Destination>
using WithValueCategoryOf =
  meta::if_<std::is_lvalue_reference<Source>,
    AddLvalueReference<Destination>,
    meta::if_<std::is_rvalue_reference<Source>,
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

namespace impl
{

template<typename T>
struct result_of : meta::id<Invoke<T>> { };

template<typename TRet, typename... TArg>
struct result_of<TRet(*)(TArg...) > : meta::id<TRet> { };

template<typename TClass, typename TRet, typename... TArg>
struct result_of<TRet(TClass::*)(TArg...)> : meta::id<TRet> { };

template<typename Fn, typename... Arg>
struct result_of<Fn(Arg...)> : meta::id<Invoke<std::result_of<Fn(Arg...)>>> { };

} // namespace impl

template<typename T>
using ResultOf = Invoke<impl::result_of<T>>;

template<typename, template<typename...> class>
struct is_specialization_of : meta::bool_<false> { };

template<template<typename...> class TTemplate, typename... TArgs>
struct is_specialization_of<TTemplate<TArgs...>, TTemplate> : meta::bool_<true> { };

}

#endif
