#ifndef MPL_CONST_HPP_
#define MPL_CONST_HPP_

#include <type_traits>

namespace mpl {

	template<typename T, T V>
	using const_ = std::integral_constant<T, V>;
}

#endif