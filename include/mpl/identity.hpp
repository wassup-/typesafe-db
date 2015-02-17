#ifndef MPL_IDENTITY_HPP_
#define MPL_IDENTITY_HPP_

namespace mpl
{

template<typename T>
struct identity { using type = T; };

template<typename T>
using identity_t = typename T::type;

}

#endif
