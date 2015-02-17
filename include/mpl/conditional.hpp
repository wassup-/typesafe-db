#ifndef MPL_CONDITIONAL_HPP_
#define MPL_CONDITIONAL_HPP_

#include "eval_if.hpp"
#include "identity.hpp"

namespace mpl
{

template<typename If, typename Then, typename Else>
using conditional = eval_if<If, Then, Else>;
template<typename If, typename Then, typename Else>
using conditional_t = identity_t<conditional<If, Then, Else>>;

}

#endif
