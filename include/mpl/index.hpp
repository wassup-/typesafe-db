#ifndef MPL_INDEX_HPP_
#define MPL_INDEX_HPP_

#include "const.hpp"

namespace mpl
{

template<std::size_t I>
using index_ = const_<std::size_t, I>;

}

#endif
