#ifndef MPL_INTEGER_SEQUENCE_HPP_
#define MPL_INTEGER_SEQUENCE_HPP_

#include "../meta.hpp"
#include "index.hpp"

namespace mpl
{

template<typename T, T... Vs>
using integer_sequence = meta::list<std::integral_constant<T, Vs>...>;

template<std::size_t... Idx>
using indices_ = integer_sequence<std::size_t, Idx...>;

template<typename T, T V, T... Vs>
using index_of_v = typename integer_sequence<T, Vs...>::template index_of<V>;

template<typename T, T V, T... Vs>
using contained_v = typename integer_sequence<T, Vs...>::template contains<V>;

}

#endif
