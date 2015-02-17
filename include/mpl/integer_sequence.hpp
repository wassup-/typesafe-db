#ifndef MPL_INTEGER_SEQUENCE_HPP_
#define MPL_INTEGER_SEQUENCE_HPP_

#include "identity.hpp"
#include "index.hpp"

namespace mpl
{

namespace detail
{

template<std::size_t, typename T, T, T...>
struct value_index;

template<std::size_t I, typename T, T V, T H, T... R>
struct value_index<I, T, V, H, R...> : value_index<(I + 1), T, V, R...> { };
template<std::size_t I, typename T, T V, T... R>
struct value_index<I, T, V, V, R...> : index_<I> { };

template<typename T, T, T...>
struct contains_value : false_ { };
template<typename T, T V, T H, T... R>
struct contains_value<T, V, H, R...> : contains_value<T, V, R...> { };
template<typename T, T V, T... R>
struct contains_value<T, V, V, R...> : true_ { };

}

template<typename T, T... Vs>
struct integer_sequence
{
  template<template<T...> class C>
  struct as : identity<C<Vs...>> { };

  template<T V>
  struct index_of : identity_t<detail::value_index<0, T, V, Vs...>> { };

  template<T V>
  struct contains : identity_t<detail::contains_value<T, V, Vs...>> { };
};

template<std::size_t... Idx>
using indices_ = integer_sequence<std::size_t, Idx...>;

template<typename T, T V, T... Vs>
using index_of_v = typename integer_sequence<T, Vs...>::template index_of<V>;

template<typename T, T V, T... Vs>
using contained_v = typename integer_sequence<T, Vs...>::template contains<V>;

}

#endif
