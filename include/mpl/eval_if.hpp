#ifndef MPL_EVAL_IF_HPP_
#define MPL_EVAL_IF_HPP_

#include "identity.hpp"
#include "if.hpp"

namespace mpl {

	template<typename If, typename Then, typename Else>
	using eval_if = identity_t<if_<If::value, Then, Else>>;
}

#endif