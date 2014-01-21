#ifndef MPL_ALL_HPP_
#define MPL_ALL_HPP_

#include "bool.hpp"
#include "eval_if.hpp"
#include "identity.hpp"

namespace mpl {

	namespace detail {

		template<typename H, typename... T>
		struct all_of : eval_if<H, all_of<T...>, false_> { };
		template<typename H>
		struct all_of<H> : eval_if<H, true_, false_> { };
	}

	template<typename... T>
	using all_ = identity_t<detail::all_of<T...>>;
}

#endif