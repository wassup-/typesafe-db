#ifndef MPL_ALL_HPP_
#define MPL_ALL_HPP_

#include "../meta.hpp"

namespace mpl
{

template<typename... T>
using all_ = meta::and_<T...>;

}

#endif
