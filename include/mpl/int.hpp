#ifndef MPL_INT_HPP_
#define MPL_INT_HPP_

#include "const.hpp"

namespace mpl
{

template<int I>
using int_ = const_<decltype(I), I>;

}

#endif
