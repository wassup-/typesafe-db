/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _INDICES_HPP
#define _INDICES_HPP

namespace fp {
	template <std::size_t...> struct indices { };
 
    template <std::size_t N, std::size_t... Is> struct build_indices : build_indices<N-1, N-1, Is...> { };
    template <std::size_t... Is> struct build_indices<0, Is...> : indices<Is...> { };
}

#endif