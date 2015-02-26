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

}

#endif
