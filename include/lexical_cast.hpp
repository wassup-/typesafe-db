/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _LEXICAL_CAST_HPP
#define _LEXICAL_CAST_HPP

#include "impl/lexical_cast_impl.hpp"

namespace fp {

    template<typename Out, typename In>
    inline Out lexical_cast(In const & v) {
        return impl::lexical_cast_impl<In, Out>::cast(v);
    }
}

#endif