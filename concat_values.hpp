/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _CONCAT_VALUES_HPP
#define _CONCAT_VALUES_HPP


namespace fp {
	template<int...> struct int_seq;
	template<typename, typename> struct concat_values;

	template<int... L, int... R> struct concat_values<int_seq<L...>, int_seq<R...> > {
		typedef int_seq<L..., R...> type;
	};
}

#endif