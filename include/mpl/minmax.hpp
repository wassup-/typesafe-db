#ifndef MPL_MINMAX_HPP_
#define MPL_MINMAX_HPP_

#include "bool.hpp"
#include "conditional.hpp"
#include "identity.hpp"

namespace mpl
{

namespace detail
{

template<typename Head, typename... Tail>
struct min
: Head
{ };

template<typename T, typename U, typename... Tail>
struct min<T, U, Tail...>
: min<conditional<bool_<(T::value < U::value)>, T, U>, Tail...>
{ };

template<typename Head, typename... Tail>
struct max
: Head
{ };

template<typename T, typename U, typename... Tail>
struct max<T, U, Tail...>
: max<conditional<bool_<(T::value > U::value)>, T, U>, Tail...>
{ };

}

template<typename... T>
using min_ = identity_t<detail::min<T...>>;

template<typename... T>
using max_ = identity_t<detail::max<T...>>;

}

#endif
