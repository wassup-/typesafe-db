#ifndef MPL_COUNT_HPP_
#define MPL_COUNT_HPP_

#include "identity.hpp"
#include "index.hpp"

namespace mpl
{

namespace detail
{

template<typename... T>
struct count : mpl::index_<0> { };
template<typename Head, typename... Tail>
struct count<Head, Tail...> : mpl::index_<(!!Head::value) + count<Tail...>::value> { };

}

template<typename... T>
using count_ = identity_t<detail::count<T...>>;

}

#endif
