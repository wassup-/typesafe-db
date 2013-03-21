#ifndef _FP_EXCEPTIONS_H
#define _FP_EXCEPTIONS_H

#include <exception>

namespace fp {
	struct exception_base : std::exception { };

	struct null_exception : exception_base { };

	struct bad_cast_exception : std::exception { };
	struct lexical_exception : bad_cast_exception { };
}

#endif