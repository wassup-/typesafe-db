#ifndef MPL_TYPE_SEQUENCE_HPP_
#define MPL_TYPE_SEQUENCE_HPP_

#include "identity.hpp"
#include "index.hpp"

namespace mpl
{

namespace detail
{

template<std::size_t, typename, typename...>
struct type_index;

template<std::size_t I, typename T, typename H, typename... R>
struct type_index<I, T, H, R...>
: type_index<(I + 1), T, R...>
{ };

template<std::size_t I, typename T, typename... R>
struct type_index<I, T, T, R...>
: index_<I>
{ };

template<typename, typename...>
struct contains_type
: false_
{ };

template<typename T, typename H, typename... R>
struct contains_type<T, H, R...>
: contains_type<T, R...>
{ };

template<typename T, typename... R>
struct contains_type<T, T, R...>
: true_
{ };

}

template<typename... Ts>
struct type_sequence
{
  template<template<typename...> class C>
  struct as : identity<C<Ts...>> { };

  template<typename T>
  struct index_of : identity_t<detail::type_index<0, T, Ts...>> { };

  template<typename T>
  struct contains : identity_t<detail::contains_type<T, Ts...>> { };
};

template<typename T, typename... Ts>
using index_of_t = typename type_sequence<Ts...>::template index_of<T>;

template<typename T, typename... Ts>
using contained_t = typename type_sequence<Ts...>::template contains<T>;

}

#endif
