#ifndef MPL_ENABLE_HPP_
#define MPL_ENABLE_HPP_

#include "identity.hpp"

namespace mpl
{

namespace detail
{

template<bool, typename T>
struct enable_if
{
	using type = T;
};

template<typename T>
struct enable_if<false, T>
{ };

}

template<typename If, typename T = void>
using enable_if = detail::enable_if<If::value, T>;

template<typename If, typename T = void>
using enable_if_t = identity_t<enable_if<If, T>>;

}

#endif
