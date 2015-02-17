#ifndef MPL_BOOL_HPP_
#define MPL_BOOL_HPP_

#include "const.hpp"

namespace mpl
{

template<bool V>
using bool_ = const_<bool, V>;

using true_ = bool_<true>;
using false_ = bool_<false>;

template<typename T>
using not_ = bool_<!T::value>;

}

#endif
