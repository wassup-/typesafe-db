#ifndef MPL_DISABLE_HPP_
#define MPL_DISABLE_HPP_

#include "../meta.hpp"

namespace mpl
{

namespace detail
{

template<bool, typename>
struct disable_if
{ };

template<typename T>
struct disable_if<false, T>
{
	using type = T;
};

}

template<typename If, typename T = void>
using disable_if = detail::disable_if<If::value, T>;

template<typename If, typename T = void>
using disable_if_t = meta::eval<disable_if<If, T> >;

}

#endif
