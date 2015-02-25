#ifndef MPL_ANY_HPP_
#define MPL_ANY_HPP_

#include "../meta.hpp"

namespace mpl
{

template<typename... T>
using any_ = meta::or_<T...>;

}

#endif
