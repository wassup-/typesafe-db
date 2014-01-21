#ifndef MPL_IS_SAME_HPP_
#define MPL_IS_SAME_HPP_

#include "bool.hpp"
#include "identity.hpp"

namespace mpl {

	namespace detail {

		template<typename, typename>
		struct is_same : identity<false_> { };
		template<typename T>
		struct is_same<T, T> : identity<true_> { };
	}

	template<typename T, typename U>
	using is_same = identity_t<detail::is_same<T, U>>;
}

#endif