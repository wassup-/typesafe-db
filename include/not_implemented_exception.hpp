#ifndef NOT_IMPLEMENTED_EXCEPTION_HPP_
#define NOT_IMPLEMENTED_EXCEPTION_HPP_

#include <stdexcept>

namespace fp {
	class not_implemented_exception : public std::runtime_error {
		using std::runtime_error::runtime_error;
	};
}

#endif
