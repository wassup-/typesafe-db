#ifndef MPL_ANY_HPP_
#define MPL_ANY_HPP_

#include "bool.hpp"
#include "eval_if.hpp"
#include "identity.hpp"

namespace mpl {

	namespace detail {

		template<typename H, typename... T>
		struct any_of : eval_if<H, true_, any_of<T...>> { };
		template<typename H>
		struct any_of<H> : eval_if<H, true_, false_> { };
	}

	template<typename... T>
	using any_ = identity_t<detail::any_of<T...>>;
}

#endif