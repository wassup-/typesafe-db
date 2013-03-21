/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

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