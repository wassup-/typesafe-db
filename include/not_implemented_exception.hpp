/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef NOT_IMPLEMENTED_EXCEPTION_HPP_
#define NOT_IMPLEMENTED_EXCEPTION_HPP_

#include <stdexcept>

namespace fp {
	class not_implemented_exception : public std::runtime_error {
		using std::runtime_error::runtime_error;
	};
}

#endif
