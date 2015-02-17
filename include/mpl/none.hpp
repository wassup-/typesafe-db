#ifndef MPL_NONE_HPP_
#define MPL_NONE_HPP_

#include "bool.hpp"
#include "conditional.hpp"
#include "identity.hpp"

namespace mpl
{

namespace detail
{

template<typename H, typename... T>
struct none_of
: conditional<H, false_, none_of<T...>>
{ };

template<typename H>
struct none_of<H>
: conditional<H, false_, true_>
{ };

}

template<typename... T>
using none_ = identity_t<detail::none_of<T...>>;

}

#endif
