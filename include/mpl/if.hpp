#ifndef MPL_IF_HPP_
#define MPL_IF_HPP_

#include "identity.hpp"

namespace mpl
{

template<bool, typename Then, typename Else>
struct if_
: identity<Then>
{ };

template<typename Then, typename Else>
struct if_<false, Then, Else>
: identity<Else>
{ };

}

#endif
